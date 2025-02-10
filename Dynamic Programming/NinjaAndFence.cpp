#include <iostream>
#include <vector>
using namespace std;

class NinjaFence
{
public:
    int Recursion(int n, int k)
    {
        if (n == 1)
            return k;
        if (n == 2)
            return k + k * (k - 1);

        return (k - 1) * (Recursion(n - 2, k) + Recursion(n - 1, k));
    }

    int Memoization(int n, int k, vector<int> &dp)
    {
        if (n == 1)
            return k;
        if (n == 2)
            return k + k * (k - 1);

        if (dp[n] != -1)
            return dp[n];

        dp[n] = (k - 1) * (Memoization(n - 2, k, dp) + Memoization(n - 1, k, dp));
        return dp[n];
    }

    int Tabulation(int n, int k)
    {
        vector<int> dp(n + 1, -1);
        dp[1] = k;
        dp[2] = k + k * (k - 1);

        for (int i = 3; i <= n; i++)
        {
            dp[i] = (k - 1) * (dp[i - 2] + dp[i - 1]);
        }
        return dp[n];
    }
};

int main()
{
    NinjaFence nf;
    int n = 3; // Example value for n
    int k = 2;  // Example value for k

    cout << "Number of ways to paint the fence (Recursion): " << nf.Recursion(n, k) << endl;

    vector<int> dp(n + 1, -1);
    cout << "Number of ways to paint the fence (Memoization): " << nf.Memoization(n, k, dp) << endl;

    cout << "Number of ways to paint the fence (Tabulation): " << nf.Tabulation(n, k) << endl;

    return 0;
}
