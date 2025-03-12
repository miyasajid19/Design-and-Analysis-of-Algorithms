#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
    vector<int> weights;
    vector<int> values;
    int n;

public:
    Solution(const vector<int> &weights, const vector<int> &values, int n)
        : weights(weights), values(values), n(n) {}

    int non_recurrsive(int capacity)
    {
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; ++i)
        {
            for (int w = 1; w <= capacity; ++w)
            {
                if (weights[i - 1] <= w)
                {
                    dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][capacity];
    }

    // recurrsive
    int recurrsive(int index, int capacity)
    {
        if (index == 0)
            return weights[0] <= capacity ? values[0] : 0;

        int inclusive = 0;
        if (weights[index] <= capacity)
            inclusive = values[index] + recurrsive(index - 1, capacity - weights[index]);

        int exclusive = recurrsive(index - 1, capacity);
        return max(inclusive, exclusive);
    }

    // memoization
    int memoization(int index, int capacity, vector<vector<int>> &dp)
    {
        if (index == 0)
            return weights[0] <= capacity ? values[0] : 0;

        if (dp[index][capacity] != -1)
            return dp[index][capacity];

        int inclusive = 0;
        if (weights[index] <= capacity)
            inclusive = values[index] + memoization(index - 1, capacity - weights[index], dp);
        int exclusive = memoization(index - 1, capacity, dp);
        dp[index][capacity] = max(inclusive, exclusive);
        return dp[index][capacity];
    }

    // tabulation
    int tabulation(int capacity)
    {
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= capacity; j++)
            {
                if (weights[i - 1] <= capacity)
                {
                    if (values[i - 1] + dp[i - 1][j - weights[i - 1]] > dp[i - 1][j])
                    {
                        dp[i][j] = values[i - 1] + dp[i - 1][j - weights[i - 1]];
                    }
                    else
                    {
                        dp[i][j] = dp[i - 1][j];
                    }
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][capacity];
    }
};

int main()
{
    vector<int> weights = {1, 3, 4, 5};
    vector<int> values = {1, 4, 5, 7};
    int n = weights.size();
    int capacity = 7;
    Solution s(weights, values, n);
    cout << "Maximum value in Knapsack = " << s.non_recurrsive(capacity) << endl;
    cout << "Maximum value in Knapsack = " << s.recurrsive(n, capacity) << endl;
    vector<vector<int>> dp(weights.size() + 1, vector<int>(capacity + 1, -1));
    cout << "Maximum value in Knapsack = " << s.memoization(n - 1, capacity, dp) << endl;
    cout << "Maximum value in Knapsack = " << s.tabulation(capacity) << endl;
    return EXIT_SUCCESS;
}
