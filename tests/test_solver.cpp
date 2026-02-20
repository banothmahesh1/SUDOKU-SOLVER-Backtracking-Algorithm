/*
 * Simple test harness for SudokuSolver (no external framework required).
 * Compile & run via CMake target "test_solver".
 */

#include "../src/SudokuSolver.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

// ---- Helpers -------------------------------------------------------------

static int passed = 0;
static int failed = 0;

#define TEST(name)                                                            \
    do {                                                                      \
        std::cout << "  " << #name << " ... ";                                \
    } while (0)

#define PASS()                                                                \
    do {                                                                      \
        std::cout << "PASSED" << std::endl;                                   \
        ++passed;                                                             \
    } while (0)

#define FAIL(msg)                                                             \
    do {                                                                      \
        std::cout << "FAILED: " << msg << std::endl;                          \
        ++failed;                                                             \
    } while (0)

// ---- Test cases ----------------------------------------------------------

void test_solve_example_puzzle() {
    TEST(solve_example_puzzle);

    std::vector<std::vector<char>> board = {
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

    std::vector<std::vector<char>> expected = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };

    SudokuSolver solver;
    bool ok = solver.solveSudoku(board);

    if (!ok) { FAIL("solver returned false"); return; }
    if (board != expected) { FAIL("solution mismatch"); return; }
    PASS();
}

void test_already_solved() {
    TEST(already_solved);

    std::vector<std::vector<char>> board = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };

    auto copy = board;
    SudokuSolver solver;
    bool ok = solver.solveSudoku(board);

    if (!ok) { FAIL("solver returned false on solved board"); return; }
    if (board != copy) { FAIL("board changed"); return; }
    PASS();
}

void test_no_solution() {
    TEST(no_solution);

    // Two 5s in the first row -> unsolvable
    std::vector<std::vector<char>> board = {
        {'5','5','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    SudokuSolver solver;
    bool ok = solver.solveSudoku(board);

    if (ok) { FAIL("solver should return false for invalid board"); return; }
    PASS();
}

void test_load_from_stream() {
    TEST(load_from_stream);

    std::string input =
        "53..7....\n"
        "6..195...\n"
        ".98....6.\n"
        "8...6...3\n"
        "4..8.3..1\n"
        "7...2...6\n"
        ".6....28.\n"
        "...419..5\n"
        "....8..79\n";

    std::istringstream iss(input);
    std::vector<std::vector<char>> board;
    bool ok = SudokuSolver::loadFromStream(iss, board);

    if (!ok) { FAIL("loadFromStream returned false"); return; }
    if (board.size() != 9) { FAIL("wrong row count"); return; }
    if (board[0][0] != '5') { FAIL("first cell mismatch"); return; }
    if (board[0][2] != '.') { FAIL("empty cell mismatch"); return; }
    PASS();
}

// ---- Runner --------------------------------------------------------------

int main() {
    std::cout << "\n=== SudokuSolver Tests ===" << std::endl;

    test_solve_example_puzzle();
    test_already_solved();
    test_no_solution();
    test_load_from_stream();

    std::cout << "\nResults: " << passed << " passed, "
              << failed << " failed." << std::endl;
    return (failed == 0) ? 0 : 1;
}
