#include "SudokuSolver.h"

#include <iostream>
#include <fstream>

// ---- Constraint check ----------------------------------------------------

bool SudokuSolver::isSafe(std::vector<std::vector<char>>& board,
                           int row, int col, char dig) {
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

// ---- Recursive backtracking solver ---------------------------------------

bool SudokuSolver::solve(std::vector<std::vector<char>>& board,
                          int row, int col) {
    if (row == 9) return true;              // all rows filled -> solved

    int nextrow = row, nextcol = col + 1;
    if (nextcol == 9) {                     // wrap to next row
        nextrow = row + 1;
        nextcol = 0;
    }
    if (board[row][col] != '.') {           // pre-filled cell -> skip
        return solve(board, nextrow, nextcol);
    }

    for (char dig = '1'; dig <= '9'; dig++) {
        if (isSafe(board, row, col, dig)) {
            board[row][col] = dig;
            if (solve(board, nextrow, nextcol)) return true;
            board[row][col] = '.';          // backtrack
        }
    }
    return false;
}

// ---- Public entry point --------------------------------------------------

bool SudokuSolver::solveSudoku(std::vector<std::vector<char>>& board) {
    return solve(board, 0, 0);
}

// ---- Pretty-print --------------------------------------------------------

void SudokuSolver::printBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "+-------+-------+-------+" << std::endl;
    for (int i = 0; i < 9; i++) {
        std::cout << "| ";
        for (int j = 0; j < 9; j++) {
            std::cout << board[i][j] << ' ';
            if ((j + 1) % 3 == 0) std::cout << "| ";
        }
        std::cout << std::endl;
        if ((i + 1) % 3 == 0)
            std::cout << "+-------+-------+-------+" << std::endl;
    }
}

// ---- I/O helpers ---------------------------------------------------------

bool SudokuSolver::loadFromFile(const std::string& path,
                                 std::vector<std::vector<char>>& board) {
    std::ifstream fin(path);
    if (!fin.is_open()) return false;
    return loadFromStream(fin, board);
}

bool SudokuSolver::loadFromStream(std::istream& in,
                                   std::vector<std::vector<char>>& board) {
    board.assign(9, std::vector<char>(9, '.'));
    for (int i = 0; i < 9; i++) {
        std::string line;
        if (!std::getline(in, line)) return false;
        if (line.size() < 9) return false;
        for (int j = 0; j < 9; j++) {
            char c = line[j];
            board[i][j] = (c == '0') ? '.' : c;
        }
    }
    return true;
}
