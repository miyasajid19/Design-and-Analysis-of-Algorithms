#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class MatrixChainMultiplication
{
    vector<int> arr;
    vector<vector<int>> cost;
    vector<vector<int>> path;

public:
    MatrixChainMultiplication(const vector<int> &arr) : arr(arr)
    {
        int n = arr.size() - 1;
        cost.resize(n + 1, vector<int>(n + 1, 0));
        path.resize(n + 1, vector<int>(n + 1, 0));
    }

    int MinimumOperations()
    {
        int n = arr.size() - 1;

        for (int l = 2; l <= n; l++)
        {
            for (int i = 1; i <= n - l + 1; i++)
            {
                int j = i + l - 1;
                cost[i][j] = INT_MAX;
                for (int k = i; k < j; k++)
                {
                    int q = cost[i][k] + cost[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                    if (q < cost[i][j])
                    {
                        cost[i][j] = q;
                        path[i][j] = k;
                    }
                }
            }
        }
        return cost[1][n];
    }

    void PrintPath(int i, int j)
    {
        if (i == j)
        {
            cout << " A" << i;
        }
        else
        {
            cout << "(";
            PrintPath(i, path[i][j]);
            PrintPath(path[i][j] + 1, j);
            cout << ")";
        }
    }

    void PrintPath()
    {
        PrintPath(1, arr.size() - 1);
    }
};

int main()
{
    vector<int> arr = {5, 4, 6, 2, 7};
    MatrixChainMultiplication obj(arr);
    cout << "The Minimum Cost is " << obj.MinimumOperations() << endl
         << "And The Optimal Parenthesization is ";
    obj.PrintPath();
    return EXIT_SUCCESS;
}
