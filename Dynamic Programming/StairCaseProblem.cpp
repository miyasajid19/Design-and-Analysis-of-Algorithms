#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class StairCase
{
    int totalTiles;
    int step_1;
    int step_2;
    vector<int> cost;

public:
    StairCase(int n, vector<int> cost)
    {
        this->totalTiles = n;
        this->step_1 = 1;
        this->step_2 = 2;
        this->cost = cost;
    }

    StairCase(int n, int a, int b, vector<int> cost) : totalTiles(n), step_1(a), step_2(b), cost(cost) {}

    // Recursion (Exponential Complexity)
    int recursion(int start)
    {
        if (start >= totalTiles) return 0;
        return cost[start] + min(recursion(start + step_1), recursion(start + step_2));
    }

    // Memoization (Top-Down Approach)
    int Memoization(int start, vector<int> &mappingVector)
    {
        if (start >= totalTiles) return 0;
        if (mappingVector[start] != -1) return mappingVector[start];

        mappingVector[start] = cost[start] + min(Memoization(start + step_1, mappingVector), Memoization(start + step_2, mappingVector));
        return mappingVector[start];
    }

    // Tabulation (Bottom-Up Approach)
    int Tabulation()
    {
        if (totalTiles == 0) return 0;
        if (totalTiles == 1) return cost[0];

        vector<int> dp(totalTiles);
        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int i = 2; i < totalTiles; i++)
        {
            dp[i] = cost[i] + min(dp[i - step_1], dp[i - step_2]);
        }
        return min(dp[totalTiles - 1], dp[totalTiles - 2]);
    }

    // Space Optimized Approach (O(1) Space Complexity)
    int spaceOptimized()
    {
        if (totalTiles == 0) return 0;
        if (totalTiles == 1) return cost[0];

        int prev1 = cost[1];
        int prev2 = cost[0];

        for (int i = 2; i < totalTiles; i++)
        {
            int current = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = current;
        }
        return min(prev1, prev2);
    }
};

int main()
{
    vector<int> cost = {10, 12, 13, 41, 52, -6, 17, 48, -9, 10};
    StairCase solver(10, 1, 2, cost);

    cout << "Recursion Cost: " << min(solver.recursion(0), solver.recursion(1)) << endl;

    vector<int> mappingVector(11, -1);
    cout << "Memoization Cost: " << min(solver.Memoization(0, mappingVector), solver.Memoization(1, mappingVector)) << endl;

    cout << "Tabulation Cost: " << solver.Tabulation() << endl;
    cout << "Space Optimized Cost: " << solver.spaceOptimized() << endl;

    return EXIT_SUCCESS;
}
