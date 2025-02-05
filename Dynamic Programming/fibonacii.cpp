#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Fibonacci
{
public:
    // Top-Down Approach with Memoization
    int TopDownApproach(int n, vector<int> &mappingVector)
    {
        if (n == 0) return 0;
        if (n == 1) return 1;

        if (mappingVector[n] != -1)
            return mappingVector[n];

        mappingVector[n] = TopDownApproach(n - 1, mappingVector) + TopDownApproach(n - 2, mappingVector);
        return mappingVector[n];
    }

    // Overloaded function to handle vector initialization internally
    int TopDownApproach(int n)
    {
        vector<int> mappingVector(n + 1, -1);
        return TopDownApproach(n, mappingVector);
    }

    // Bottom-Up Approach (Tabulation)
    int BottomUpApproach(int n)
    {
        if (n == 0) return 0;
        if (n == 1) return 1;

        vector<int> mappingVector(n + 1, 0);
        mappingVector[0] = 0;
        mappingVector[1] = 1;

        for (int i = 2; i <= n; i++)
            mappingVector[i] = mappingVector[i - 1] + mappingVector[i - 2];

        return mappingVector[n];
    }
};

int main()
{
    int n;
    cout << "Enter the value for Nth Fibonacci term: ";
    cin >> n;

    if (n < 0) {
        cout << "Fibonacci sequence is not defined for negative numbers." << endl;
        return EXIT_FAILURE;
    }

    Fibonacci fibo;
    
    cout << "The Fibonacci term (Top-Down Approach): " << fibo.TopDownApproach(n) << endl;
    cout << "The Fibonacci term (Bottom-Up Approach): " << fibo.BottomUpApproach(n) << endl;

    return EXIT_SUCCESS;
}
