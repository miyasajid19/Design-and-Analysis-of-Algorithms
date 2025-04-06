#include <iostream>
#include <vector>
#include <string>
using namespace std;
class NQueenProblem
{
    vector<vector<int>> board;
    vector<vector<int>> solutions;
    int n;
    bool isSafe(int row, int column)
    {
        // check for the row
        for (int i = 0; i < column; i++)
        {
            if (board[row][i] == 1)
                return false;
        }

        // check for upper diagonal on left side
        for (int i = row, j = column; i >= 0 && j >= 0; i--, j--)
        {
            if (board[i][j] == 1)
                return false;
        }

        // check for the lower diagonal on left side
        for (int i = row, j = column; j >= 0 && i < n; i++, j--)
        {
            if (board[i][j] == 1)
                return false;
        }

        return true;
    }

    void converter()
    {
        vector<int> temp;
        for (auto x : board)
        {
            for (auto y : x)
            {
                temp.push_back(y);
            }
        }
        solutions.push_back(temp);
    }
    void solveNQueenUtil(int column)
    {
        if (column == n)
        {
            converter();
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (isSafe(i, column))
            {
                board[i][column] = 1;        // Place the queen
                solveNQueenUtil(column + 1); // Recur to place the rest of the queens
                board[i][column] = 0;        // Backtrack: remove the queen
            }
        }
    }

public:
    NQueenProblem(int n) : n(n)
    {
        board.resize(n, vector<int>(n, 0)); // Initialize the chessboard with 0s
    }

    vector<vector<int>> solveNQueens()
    {
        solveNQueenUtil(0);
        return solutions;
    }
};
int main()
{
    int n;
    cout << "Enter the size of the chessboard: ";
    cin >> n;
    NQueenProblem nQueen(n);
    vector<vector<int>> solutions = nQueen.solveNQueens();
    cout << "Solutions:" << endl;
    for (const auto &solution : solutions)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << solution[i * n + j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    if (solutions.empty())
    {
        cout << "No solution exists." << endl;
    }
    else
    {
        cout << "Total solutions: " << solutions.size() << endl;
    }
    return 0;
}