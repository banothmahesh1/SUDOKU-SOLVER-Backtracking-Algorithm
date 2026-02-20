#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <vector>
#include <string>

class SudokuSolver {
public:
    /// Solve the board in-place. Returns true if a solution exists.
    bool solveSudoku(std::vector<std::vector<char>>& board);

    /// Pretty-print the board to stdout.
    static void printBoard(const std::vector<std::vector<char>>& board);

    /// Load a board from a text file (9 lines, 9 chars each).
    static bool loadFromFile(const std::string& path,
                             std::vector<std::vector<char>>& board);

    /// Load a board from an input stream.
    static bool loadFromStream(std::istream& in,
                               std::vector<std::vector<char>>& board);

private:
    bool isSafe(std::vector<std::vector<char>>& board,
                int row, int col, char dig);
    bool solve(std::vector<std::vector<char>>& board,
               int row, int col);
};

#endif // SUDOKU_SOLVER_H
