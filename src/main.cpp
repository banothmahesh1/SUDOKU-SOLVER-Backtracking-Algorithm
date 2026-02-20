#include "SudokuSolver.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "         SUDOKU SOLVER" << std::endl;
    std::cout << "========================================" << std::endl;

    std::vector<std::vector<char>> board;
    bool loaded = false;

    if (argc >= 2) {
        // Load from file supplied as first argument
        std::string path = argv[1];
        loaded = SudokuSolver::loadFromFile(path, board);
        if (!loaded) {
            std::cerr << "Error: could not read puzzle from " << path << std::endl;
            return 1;
        }
    } else {
        // Interactive menu
        int choice;
        std::cout << "\n1. Use sample puzzle" << std::endl;
        std::cout << "2. Enter your own puzzle (9 rows of 9 chars)" << std::endl;
        std::cout << "Enter choice (1 or 2): ";
        std::cin >> choice;

        if (choice == 2) {
            std::cout << "\nEnter the 9x9 Sudoku board row by row." << std::endl;
            std::cout << "Use '.' or '0' for empty cells.\n" << std::endl;
            // consume leftover newline
            std::string dummy;
            std::getline(std::cin, dummy);

            loaded = SudokuSolver::loadFromStream(std::cin, board);
            if (!loaded) {
                std::cerr << "Error: invalid input." << std::endl;
                return 1;
            }
        } else {
            // Built-in sample puzzle
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
            loaded = true;
        }
    }

    std::cout << "\n--- Unsolved Board ---" << std::endl;
    SudokuSolver::printBoard(board);

    SudokuSolver solver;
    if (solver.solveSudoku(board)) {
        std::cout << "\n--- Solved Board ---" << std::endl;
        SudokuSolver::printBoard(board);
        std::cout << "\nSudoku solved successfully!" << std::endl;
    } else {
        std::cout << "\nNo solution exists for the given board." << std::endl;
        return 1;
    }

    return 0;
}
