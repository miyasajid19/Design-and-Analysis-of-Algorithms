#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find the length of the longest common subsequence
//tabulation
int longestCommonSubsequence(const string &text1, const string &text2) {
    int m = text1.size();
    int n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

// Main function
int main() {
    string text1, text2;
    cout << "Enter the first string: ";
    cin >> text1;
    cout << "Enter the second string: ";
    cin >> text2;

    int lcsLength = longestCommonSubsequence(text1, text2);
    cout << "The length of the longest common subsequence is: " << lcsLength << endl;

    return 0;
}