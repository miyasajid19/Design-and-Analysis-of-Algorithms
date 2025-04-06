#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
class SudokuSolver
{
    vector<vector<int>> board;
    int N;
    bool isSafe(int row, int column, int value)
    {
        // check the row
        for (int i = 0; i < N; i++)
        {
            if (board[row][i] == value)
                return false;
        }

        // check the column
        for (int i = 0; i < N; i++)
        {
            if (board[i][column] == value)
                return false;
        }

        // check the 3*3 grid
        int startRow = row - row % 3;
        int startColumn = column - column % 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i + startRow][j + startColumn] == value)
                    return false;
            }
        }
        return true;
    }

public:
    SudokuSolver(vector<vector<int>> board)
    {
        this->board = board;
        N = board[0].size();
    }

    bool solve()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] != 0)
                {
                    continue;
                }
                // try all possible values from 1 to 9
                for (int value = 1; value <= 9; i++)
                {
                    if (isSafe(i, j, value))
                    {
                        board[i][j] = value;
                        if (solve())
                        {
                            return true;
                        }
                        // backtrack
                        board[i][j] = 0;
                    }
                }
                // if no value is valid, return false
                return false;
            }
        }
        // if we reach here, it means we have solved the sudoku
        return true;
    }
};
int main()
{
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 5, 3, 8, 6, 7, 9, 2}};
    SudokuSolver solver(board);
    if (solver.solve())
    {
        cout << "Sudoku solved successfully!" << endl;
        for (const auto &row : board)
        {
            for (int num : row)
            {
                cout << num << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No solution exists!" << endl;
    }
    return EXIT_SUCCESS;
}