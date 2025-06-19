#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <unordered_map>
using namespace std;

// Class definition to handle all three approaches
class MatrixChainMultiplication
{
    vector<int> arr; // Dimensions of matrices

    // Memoization storage
    unordered_map<string, int> memo;

    // Tabulation table
    vector<vector<int>> tabulationTable;
    vector<vector<int>> splitTable; // To store the splits

public:
    MatrixChainMultiplication(const vector<int> &arr) : arr(arr) {}

    // Recursive approach
    int recursiveSolution(int i, int j)
    {
        if (i == j)
        {
            return 0; // No cost to multiply one matrix
        }

        int minCost = INT_MAX;
        for (int k = i; k < j; k++)
        {
            int cost = recursiveSolution(i, k) + recursiveSolution(k + 1, j) + arr[i - 1] * arr[k] * arr[j];
            minCost = min(minCost, cost);
        }
        return minCost;
    }

    // Memoization approach
    int memoizedSolution(int i, int j)
    {
        if (i == j)
        {
            return 0; // No cost to multiply one matrix
        }

        string key = to_string(i) + "," + to_string(j);
        if (memo.find(key) != memo.end())
        {
            return memo[key]; // Return already computed value
        }

        int minCost = INT_MAX;
        for (int k = i; k < j; k++)
        {
            int cost = memoizedSolution(i, k) + memoizedSolution(k + 1, j) + arr[i - 1] * arr[k] * arr[j];
            minCost = min(minCost, cost);
        }
        memo[key] = minCost; // Store result in memo table
        return minCost;
    }

    // Tabulation approach
    int tabulationSolution()
    {
        int n = arr.size() - 1;
        tabulationTable.resize(n + 1, vector<int>(n + 1, 0));
        splitTable.resize(n + 1, vector<int>(n + 1, 0));

        for (int l = 2; l <= n; l++)
        { // Chain length
            for (int i = 1; i <= n - l + 1; i++)
            {
                int j = i + l - 1;
                tabulationTable[i][j] = INT_MAX;

                for (int k = i; k < j; k++)
                {
                    int cost = tabulationTable[i][k] + tabulationTable[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                    if (cost < tabulationTable[i][j])
                    {
                        tabulationTable[i][j] = cost;
                        splitTable[i][j] = k;
                    }
                }
            }
        }
        return tabulationTable[1][n];
    }

    // Function to print optimal parenthesization
    void printOptimalParenthesization(int i, int j)
    {
        if (i == j)
        {
            cout << " A" << i;
        }
        else
        {
            cout << "(";
            printOptimalParenthesization(i, splitTable[i][j]);
            printOptimalParenthesization(splitTable[i][j] + 1, j);
            cout << ")";
        }
    }

    // Function to demonstrate all approaches
    void demonstrateSolutions()
    {
        int n = arr.size() - 1;
        cout << "Using Recursion: " << recursiveSolution(1, n) << endl;
        cout << "Using Memoization: " << memoizedSolution(1, n) << endl;
        cout << "Using Tabulation: " << tabulationSolution() << endl;
        // Print split table for tabulation
        cout << "Split Table: " << endl;
        printf("0 |1|2|3|4|5|6|7|8|9\n");
        for (int i = 1; i <= n; i++)
        {
            printf("%d |", i);
            for (int j = 1; j <= n; j++)
            {
                cout << splitTable[i][j] << "|";
            }
            cout << endl;
        }
        

        cout << "Optimal Parenthesization: ";
        printOptimalParenthesization(1, n);
        cout << endl;
    }
};

int main()
{
    vector<int> arr = {1, 33,5, 1, 12, 1,7,18,4,1};
    MatrixChainMultiplication obj(arr);
    obj.demonstrateSolutions();
    return 0;
}
