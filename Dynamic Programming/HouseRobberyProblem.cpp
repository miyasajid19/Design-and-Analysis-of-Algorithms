#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

class HouseRobberySolver
{
    int Recursion(const vector<int>& array, int n)
    {
        if (n < 0)
            return 0;
        if (n == 0)
            return array[0];
        int inclusion = Recursion(array, n - 2) + array[n];
        int exclusion = Recursion(array, n - 1);
        return max(inclusion, exclusion);
    }

    int Memoization(const vector<int>& array, vector<int>& mappingVector, int n)
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

    int Tabulation(const vector<int>& array)
    {
        int n = array.size();
        vector<int> mappingVector(n, 0);
        mappingVector[0] = array[0];
        for (int i = 1; i < n; i++)
        {
            int inclusive = array[i];
            if (i > 1)
            {
                inclusive += mappingVector[i - 2];
            }
            int exclusive = mappingVector[i - 1];
            mappingVector[i] = max(inclusive, exclusive);
        }
        return mappingVector[n - 1];
    }

    int SpaceOptimized(const vector<int>& array)
    {
        int n = array.size();
        if (n == 1) return array[0];
        int previous_2 = 0;
        int previous_1 = array[0];
        for (int i = 1; i < n; i++)
        {
            int inclusive = previous_2 + array[i];
            int exclusive = previous_1;
            int ans = max(inclusive, exclusive);
            previous_2 = previous_1;
            previous_1 = ans;
        }
        return previous_1;
    }

public:
    void HouseRobbery(const vector<int>& array)
    {
        int n = array.size();
        if (n == 1)
        {
            cout << "The maximum amount that can be collected is: " << array[0] << endl;
            return;
        }

        vector<int> first(array.begin(), array.end() - 1);
        vector<int> last(array.begin() + 1, array.end());

        cout << "Using Recursion, the maximum non-adjacent sum is: " << max(Recursion(first, first.size() - 1), Recursion(last, last.size() - 1)) << endl;

        vector<int> mappingVector(array.size(), -1);
        cout << "Using Memoization, the maximum non-adjacent sum is: " << max(Memoization(first, mappingVector, first.size() - 1), Memoization(last, mappingVector, last.size() - 1)) << endl;

        cout << "Using Tabulation, the maximum non-adjacent sum is: " << max(Tabulation(first), Tabulation(last)) << endl;

        cout << "Using Space Optimization, the maximum non-adjacent sum is: " << max(SpaceOptimized(first), SpaceOptimized(last)) << endl;
    }
};

int main()
{
    vector<int> CostInEachHouse = {3, 6, 5};
    HouseRobberySolver solver;
    solver.HouseRobbery(CostInEachHouse);
    return EXIT_SUCCESS;
}
