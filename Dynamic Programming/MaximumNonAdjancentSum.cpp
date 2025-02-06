#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
class MaximumNonAdjancentSum
{

public:
    int Recurrsion(vector<int> array, int n)
    {
        if (n < 0)
            return 0;
        if (n == 0)
            return array[0];
        int inclusion = Recurrsion(array, n - 2) + array[n];
        int exclusion = Recurrsion(array, n - 1);
        return max(inclusion, exclusion);
    }

    int Memoization(vector<int> array, vector<int> &mappingVector, int n)
    {
        if (n < 0)
            return 0;

        if (n == 0)
            return array[0];

        if (mappingVector[n] != -1)
            return mappingVector[n];

        int inclusive = Memoization(array, mappingVector, n - 2) + array[n];
        int exclusive = Memoization(array, mappingVector, n - 1);
        mappingVector[n] = max(inclusive, exclusive);
        return mappingVector[n];
    }

    int Tabulation(vector<int> array)
    {
        int n = array.size();
        vector<int> MappingVector(n, 0);

        MappingVector[0] = array[0];
        for (int i = 1; i < n; i++)
        {

            int inclusive = array[i];
            if (i > 1)
            {
                inclusive += MappingVector[i - 2];
            }
            int exclusive = MappingVector[i - 1];
            MappingVector[i] = max(inclusive, exclusive);
        }
        return MappingVector[n - 1];
    }
    int spaceOptimized(vector<int> array)
    {
        int n = array.size();
        int previous_2 = array[0];
        int previous_1 = array[1];
        for (int i = 2; i < n; i++)
        {
            int inclusive = previous_2 + array[i];
            int exclusive = previous_1;
            int ans = max(inclusive, exclusive);
            previous_2 = previous_1;
            previous_1 = ans;
        }
        return previous_1;
    }
};

int main()
{
    vector<int> array = {1, 5, 3, 2, 1, 6, 1, 5};
    MaximumNonAdjancentSum solver;

    cout << "Using Recursion, the maximum non-adjacent sum is: " << solver.Recurrsion(array, array.size() - 1) << endl;

    vector<int> mappingVector(array.size(), -1);
    cout << "Using Memoization, the maximum non-adjacent sum is: " << solver.Memoization(array, mappingVector, array.size() - 1) << endl;

    cout << "Using Tabulation, the maximum non-adjacent sum is: " << solver.Tabulation(array) << endl;

    cout << "Using Space Optimization, the maximum non-adjacent sum is: " << solver.spaceOptimized(array) << endl;

    return EXIT_SUCCESS;
}