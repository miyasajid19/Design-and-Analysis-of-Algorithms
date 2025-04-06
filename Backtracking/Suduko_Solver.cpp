#include <iostream>
#include <vector>
using namespace std;

class SudokuSolver
{
    vector<vector<int>> board;
    int N;

    bool isSafe(int row, int column, int value)
    {
        // Check the row
        for (int i = 0; i < N; i++)
        {
            if (board[row][i] == value)
                return false;
        }

        // Check the column
        for (int i = 0; i < N; i++)
        {
            if (board[i][column] == value)
                return false;
        }

        // Check the 3x3 grid
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

    bool solveSudoku()
    {
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                if (board[row][col] != 0)
                {
                    continue;
                }

                // Try all possible values from 1 to 9
                for (int value = 1; value <= 9; value++)
                {
                    if (isSafe(row, col, value))
                    {
                        board[row][col] = value;

                        if (solveSudoku())
                        {
                            return true;
                        }

                        // Backtrack
                        board[row][col] = 0;
                    }
                }

                // If no value is valid, return false
                return false;
            }
        }

        // If we reach here, it means the Sudoku is solved
        return true;
    }

public:
    SudokuSolver(const vector<vector<int>> &inputBoard) : board(inputBoard), N(inputBoard.size()) {}

    bool solve()
    {
        return solveSudoku();
    }

    void printBoard() const
    {
        for (const auto &row : board)
        {
            for (int num : row)
            {
                cout << num << " ";
            }
            cout << endl;
        }
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
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    SudokuSolver solver(board);

    if (solver.solve())
    {
        cout << "Sudoku solved successfully!" << endl;
        solver.printBoard();
    }
    else
    {
        cout << "No solution exists!" << endl;
    }

    return EXIT_SUCCESS;
}
