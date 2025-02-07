#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class countDerangements
{
public:
    int Recursion(vector<int> array, int n)
    {
        if (n == 1)
            return 0;

        if (n == 2)
            return 1;

        return (n - 1) * (Recursion(array, n - 1) + Recursion(array, n - 2));
    }

    int Memoization(vector<int> array, int n, vector<int> &mappingVector)
    {
        if (n == 1)
            return 0;

        if (n == 2)
            return 1;
        if (mappingVector[n] != -1)
            return mappingVector[n - 1];

        mappingVector[n] = (n - 1) * (Memoization(array, n - 1, mappingVector) + Memoization(array, n - 2, mappingVector));
        return mappingVector[n];
    }

    int Tabulation(vector<int> array)
    {
        int n = array.size()+1;
        vector<int> mappingVector(n);

        mappingVector[1] = 0;
        mappingVector[2] = 1;
        for (int i = 3; i < n; i++)
        {
            mappingVector[i] = (i - 1) * (mappingVector[i - 1] + mappingVector[i - 2]);
        }
        return mappingVector[n-1];
    }

    int spaceOptimized(vector<int>array)
    {
        int previous_2=0;
        int previous_1=1;
        for (int i =2;i<=array.size();i++)
        {
            int current = (i-1)*(previous_1+previous_2);
            previous_2=previous_1;
            previous_1=current;
        }
        return previous_1;
    }
};

int main()
{
    vector<int> array = {0, 1, 2,4,5,6,7};
    countDerangements solver;
    cout << "Total No. of Dearangements (Recursion) :: " << solver.Recursion(array, array.size()) << endl;
    vector<int> mappingVector(array.size() + 1, -1);
    cout << "Total No. of Dearangements (Memoization) :: " << solver.Memoization(array, array.size(), mappingVector) << endl;
    cout << "Total No. of Dearangements (Tabulation) :: " << solver.Tabulation(array) << endl;
    cout << "Total No. of Dearangements (Tabulation) :: " << solver.spaceOptimized(array) << endl;

    return EXIT_SUCCESS;
}