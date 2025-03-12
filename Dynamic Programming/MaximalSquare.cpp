#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
    vector<vector<int>> array;
    int row, column;

public:
    Solution(const vector<vector<int>> &array) : array(array), row(array.size()), column(array[0].size()) {}

    int recursive(int i, int j, int &maximumSquare)
    {
        if (i >= row || j >= column)
        {
            return 0;
        }

        int right = recursive(i, j + 1, maximumSquare);
        int diagonal = recursive(i + 1, j + 1, maximumSquare);
        int down = recursive(i + 1, j, maximumSquare);

        if (array[i][j] == 1)
        {
            int ans = 1 + min({right, down, diagonal});
            maximumSquare = max(maximumSquare, ans);
            return ans;
        }
        return 0;
    }

    int maxSquare()
    {
        int maximumSquare = 0;
        recursive(0, 0, maximumSquare);
        return maximumSquare * maximumSquare;
    }

    int memoization(int i, int j, vector<vector<int>> &dp, int &maximumSquare)
    {
        if (i >= row || j >= column)
        {
            return 0;
        }
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        int right = memoization(i, j + 1, dp, maximumSquare);
        int diagonal = memoization(i + 1, j + 1, dp, maximumSquare);
        int down = memoization(i + 1, j, dp, maximumSquare);

        if (array[i][j] == 1)
        {
            int ans = 1 + min({right, down, diagonal});
            dp[i][j] = ans;
            maximumSquare = max(maximumSquare, ans);
            return ans;
        }
        dp[i][j] = 0;
        return 0;
    }

    int maxSquareMemoization()
    {
        vector<vector<int>> dp(row, vector<int>(column, -1));
        int maximumSquare = 0;
        memoization(0, 0, dp, maximumSquare);
        return maximumSquare * maximumSquare;
    }

    // tabulation
    int Tabulation()
    {
        vector<vector<int>> dp(row, vector<int>(column, 0));
        int maximumSquare = 0;

        for (int i=row-1;i>=0;i--)
        {
            for (int j=column-1;j>=0;j--)
            {
                if (i==row-1 || j==column-1)
                {
                    dp[i][j]=array[i][j];
                }
                else if (array[i][j]==1)
                {
                    dp[i][j]=1+min({dp[i+1][j],dp[i][j+1],dp[i+1][j+1]});
                }
                maximumSquare=max(maximumSquare,dp[i][j]);
            }
        }
        return maximumSquare*maximumSquare;
    }
};

int main()
{
    vector<vector<int>> array = {
        {1, 0, 1, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0}};

    Solution sol(array);
    cout << "The Maximum Possible area of Square Matrix is " << sol.maxSquare() << endl;
    cout << "The Maximum Possible area of Square Matrix using Memoization is " << sol.maxSquareMemoization() << endl;
    cout << "The Maximum Possible area of Square Matrix using Tabulation is " << sol.Tabulation() << endl;

    return EXIT_SUCCESS;
}
