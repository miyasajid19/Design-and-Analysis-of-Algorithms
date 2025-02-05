#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class Fibonacci
{
public:
    int TopDownApproach(int n, vector<int> &mappingVector)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;

        if (mappingVector[n] != -1)
            return mappingVector[n];

        mappingVector[n] = TopDownApproach(n - 1, mappingVector) + TopDownApproach(n - 2, mappingVector);
        return mappingVector[n];
    }
};
int main()
{
    // #ifndef ONLINE_JUDGE
    //     freopen("input.txt", "r", stdin);
    //     freopen("output.txt", "w", stdout);
    // #endif
    int n;
    cout << "Enter the value for Nth fibonacci series :: ";
    cin >> n;
    Fibonacci fibo;
    vector<int> mappingVector(n + 1, -1);
    cout << "The Fibonacci term is :: " << fibo.TopDownApproach(n, mappingVector);
    return EXIT_SUCCESS;
}