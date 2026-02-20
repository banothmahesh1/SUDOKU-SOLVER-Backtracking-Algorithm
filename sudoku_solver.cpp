/*
 * ========================================
 *        SUDOKU SOLVER (Backtracking)
 * ========================================
 *  - Uses recursive backtracking to fill
 *    every empty cell ('.' or '0') with a
 *    valid digit 1-9.
 *  - Checks row, column, and 3x3 sub-grid
 *    constraints before placing a digit.
 * ========================================
 */

#include <iostream>
#include <vector>
using namespace std;

class SudokuSolver {
public:
    // ---- Constraint check ------------------------------------------------
    bool isSafe(vector<vector<char>>& board, int row, int col, char dig) {
        // Check the row
        for (int j = 0; j < 9; j++) {
            if (board[row][j] == dig) return false;
        }
        // Check the column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == dig) return false;
        }
        // Check the 3x3 sub-grid
        int strow = (row / 3) * 3;
        int stcol = (col / 3) * 3;
        for (int i = strow; i <= strow + 2; i++) {
            for (int j = stcol; j <= stcol + 2; j++) {
                if (board[i][j] == dig) return false;
            }
        }
        return true;
    }

    // ---- Recursive solver ------------------------------------------------
    bool solve(vector<vector<char>>& board, int row, int col) {
        if (row == 9) return true;          // all rows filled → solved

        int nextrow = row, nextcol = col + 1;
        if (nextcol == 9) {                 // move to next row
            nextrow = row + 1;
            nextcol = 0;
        }
        if (board[row][col] != '.') {       // pre-filled cell → skip
            return solve(board, nextrow, nextcol);
        }

        for (char dig = '1'; dig <= '9'; dig++) {
            if (isSafe(board, row, col, dig)) {
                board[row][col] = dig;
                if (solve(board, nextrow, nextcol)) return true;
                board[row][col] = '.';      // backtrack
            }
        }
        return false;
    }

    // ---- Public entry point ----------------------------------------------
    bool solveSudoku(vector<vector<char>>& board) {
        return solve(board, 0, 0);
    }
};

// ---- Pretty-print the board ---------------------------------------------
void printBoard(const vector<vector<char>>& board) {
    cout << "+-------+-------+-------+" << endl;
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0)
            cout << "+-------+-------+-------+" << endl;
    }
}

// ---- Main ---------------------------------------------------------------
int main() {
    cout << "========================================" << endl;
    cout << "         SUDOKU SOLVER" << endl;
    cout << "========================================" << endl;

    int choice;
    cout << "\n1. Use sample puzzle" << endl;
    cout << "2. Enter your own puzzle" << endl;
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    vector<vector<char>> board(9, vector<char>(9, '.'));

    if (choice == 2) {
        cout << "\nEnter the 9x9 Sudoku board row by row." << endl;
        cout << "Use '.' or '0' for empty cells.\n" << endl;
        for (int i = 0; i < 9; i++) {
            cout << "Row " << i + 1 << ": ";
            for (int j = 0; j < 9; j++) {
                char c;
                cin >> c;
                board[i][j] = (c == '0') ? '.' : c;
            }
        }
    } else {
        // Sample puzzle
        board = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };
    }

    cout << "\n--- Unsolved Board ---" << endl;
    printBoard(board);

    SudokuSolver solver;
    if (solver.solveSudoku(board)) {
        cout << "\n--- Solved Board ---" << endl;
        printBoard(board);
        cout << "\nSudoku solved successfully!" << endl;
    } else {
        cout << "\nNo solution exists for the given board." << endl;
    }

    return 0;
}