#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;
class NQueenProblem
{
    vector<vector<int>> board;
    vector<vector<int>> solutions;
    unordered_map<int, bool> rowMap;           // Maps row index to column index of the queen placed in that row
    unordered_map<int, bool> leftDiagonalMap;  // Maps left diagonal index to column index of the queen placed in that diagonal
    unordered_map<int, bool> rightDiagonalMap; // Maps right diagonal index to column index of the queen placed in that diagonal
    int n;
    void convertor()
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
    bool isSafe(int row, int column)
    {
        // Check if the row is already occupied by a queen
        if (rowMap[row])
            return false;
        // Check if the left diagonal is already occupied by a queen
        if (leftDiagonalMap[row - column])
            return false;
        // Check if the right diagonal is already occupied by a queen
        if (rightDiagonalMap[(n - 1) - (row + column)])
            return false;
        // Check if the column is already occupied by a queen
        return true;
    }
    void solveNQueenUtil(int column)
    {
        if (column == n)
        {
            convertor(); // Convert the current board configuration to a solution
            return;
        }

        for (int i = 1; i <= n; i++)
        {
            if (isSafe(i - 1, column)) // Check if it's safe to place a queen at (i-1, column)
            {
                board[i - 1][column] = 1;                            // Place the queen
                rowMap[i - 1] = true;                                // Mark the row as occupied
                leftDiagonalMap[i - 1 - column] = true;              // Mark the left diagonal as occupied
                rightDiagonalMap[(n - 1) - (i - 1 + column)] = true; // Mark the right diagonal as occupied

                solveNQueenUtil(column + 1); // Recur to place the next queen

                // Backtrack: remove the queen and unmark the maps
                board[i - 1][column] = 0;
                rowMap[i - 1] = false;
                leftDiagonalMap[i - 1 - column] = false;
                rightDiagonalMap[(n - 1) - (i - 1 + column)] = false;
            }
        }
    }

public:
    NQueenProblem(int n) : n(n)
    {
        board.resize(n, vector<int>(n, 0));        // Initialize the board with 0s
        int diagonal = int(ceil(sqrt(2 * n * n))); // Calculate the maximum diagonal length
        for (int i = 0; i < diagonal; i++)
        {
            leftDiagonalMap[i] = false;  // Initialize left diagonal map
            rightDiagonalMap[i] = false; // Initialize right diagonal map
        }
        for (int i = 0; i < n; i++)
        {
            rowMap[i] = false; // Initialize row map
        }
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
    cout << "Enter the size of the board: ";
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
        cout << "No solution exists" << endl;
    }
    else
    {
        cout << "Total solutions: " << solutions.size() << endl;
    }
    return 0;
}