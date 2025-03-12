#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    vector<int> weights;
    vector<int> values;
    int n;

public:
    Solution(const vector<int>& weights, const vector<int>& values, int n)
        : weights(weights), values(values), n(n) {}

    int knapSack(int capacity) {
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int w = 1; w <= capacity; ++w) {
                if (weights[i - 1] <= w) {
                    dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][capacity];
    }
};

int main() {
    vector<int> weights = {1, 3, 4, 5};
    vector<int> values = {1, 4, 5, 7};
    int n = weights.size();
    Solution s(weights, values, n);
    cout << "Maximum value in Knapsack = " << s.knapSack(7) << endl;
    return EXIT_SUCCESS;
}
