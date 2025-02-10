#include <iostream>
#include <vector>
using namespace std;

class KnapSack
{
public:
    int Recurrsive(const vector<int> &weight, const vector<int> &values, int index, int capacity)
    {
        if (index == 0)
        {
            return (weight[0] <= capacity) ? values[0] : 0;
        }

        int inclusive = 0;
        if (weight[index] <= capacity)
        {
            inclusive = values[index] + Recurrsive(weight, values, index - 1, capacity - weight[index]);
        }
        int exclusive = Recurrsive(weight, values, index - 1, capacity);

        return max(inclusive, exclusive);
    }

    int Memoization(const vector<int> &weight, const vector<int> &values, int index, int capacity, vector<vector<int>> &dp)
    {
        if (index == 0)
        {
            return (weight[0] <= capacity) ? values[0] : 0;
        }
        if (dp[index][capacity] != -1)
        {
            return dp[index][capacity];
        }

        int inclusive = 0;
        if (weight[index] <= capacity)
        {
            inclusive = values[index] + Memoization(weight, values, index - 1, capacity - weight[index], dp);
        }
        int exclusive = Memoization(weight, values, index - 1, capacity, dp);

        dp[index][capacity] = max(inclusive, exclusive);
        return dp[index][capacity];
    }

    int Tabulation(const vector<int> &weights, const vector<int> &values, int n, int capacity)
    {
        vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

        for (int w = weights[0]; w <= capacity; ++w)
        {
            dp[0][w] = values[0];
        }

        for (int i = 1; i < n; ++i)
        {
            for (int w = 0; w <= capacity; ++w)
            {
                int inclusive = (w >= weights[i]) ? values[i] + dp[i - 1][w - weights[i]] : 0;
                int exclusive = dp[i - 1][w];
                dp[i][w] = max(inclusive, exclusive);
            }
        }

        return dp[n - 1][capacity];
    }

    int SpaceOptimized(const vector<int> &weights, const vector<int> &values, int n, int capacity)
    {
        vector<int> previous(capacity + 1, 0);
        vector<int> current(capacity + 1, 0);

        for (int w = weights[0]; w <= capacity; ++w)
        {
            previous[w] = values[0];
        }

        for (int i = 1; i < n; ++i)
        {
            for (int w = 0; w <= capacity; ++w)
            {
                int inclusive = (w >= weights[i]) ? values[i] + previous[w - weights[i]] : 0;
                int exclusive = previous[w];
                current[w] = max(inclusive, exclusive);
            }
            previous = current;
        }

        return previous[capacity];
    }

    int MoreOptimized(const vector<int> &weights, const vector<int> &values, int n, int capacity)
    {
        vector<int> dp(capacity + 1, 0);

        for (int i = 0; i < n; ++i)
        {
            for (int w = capacity; w >= weights[i]; --w)
            {
                dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
            }
        }

        return dp[capacity];
    }
};

int main()
{
    vector<int> weight = {1, 3, 5, 7};
    vector<int> values = {1, 4, 2, 7};
    int capacity = 13;
    KnapSack ks;

    int max_value = ks.Recurrsive(weight, values, weight.size() - 1, capacity);
    cout << "Maximum value in Knapsack = " << max_value << endl;

    vector<vector<int>> dp(weight.size(), vector<int>(capacity + 1, -1));
    int max_value_memo = ks.Memoization(weight, values, weight.size() - 1, capacity, dp);
    cout << "Maximum value in Knapsack with Memoization = " << max_value_memo << endl;

    int max_value_tab = ks.Tabulation(weight, values, weight.size(), capacity);
    cout << "Maximum value in Knapsack with Tabulation = " << max_value_tab << endl;

    int max_value_space_opt = ks.SpaceOptimized(weight, values, weight.size(), capacity);
    cout << "Maximum value in Knapsack with Space Optimization = " << max_value_space_opt << endl;

    int max_value_more_opt = ks.MoreOptimized(weight, values, weight.size(), capacity);
    cout << "Maximum value in Knapsack with More Optimization = " << max_value_more_opt << endl;

    return EXIT_SUCCESS;
}
