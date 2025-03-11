#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

class Solution
{
    string str1, str2;
    vector<vector<int>> dp;

public:
    Solution(const string &str1, const string &str2) : str1(str1), str2(str2)
    {
        dp.resize(str1.size() + 1, vector<int>(str2.size() + 1, -1));
    }

    int recursion(int i=0, int j=0)
    {
        if (i == str1.size() || j == str2.size())
            return 0;
        if (str1[i] == str2[j])
            return 1 + recursion(i + 1, j + 1);
        else
            return max(recursion(i + 1, j), recursion(i, j + 1));
    }

    int memoization(int i=0, int j=0)
    {
        if (i == str1.size() || j == str2.size())
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (str1[i] == str2[j])
            dp[i][j] = 1 + memoization(i + 1, j + 1);
        else
            dp[i][j] = max(memoization(i + 1, j), memoization(i, j + 1));
        return dp[i][j];
    }

    int tabulation()
    {
        int m = str1.size();
        int n = str2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};

int main()
{
    Solution soln("abcde", "cade");
    cout << "recurrsion :: " << soln.recursion() << endl;
    cout << "memoization :: " << soln.memoization() << endl;
    cout << "tabulation :: " << soln.tabulation() << endl;
    return EXIT_SUCCESS;
}
