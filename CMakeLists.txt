cmake_minimum_required(VERSION 3.14)
project(sudokuSolver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Main executable ------------------------------------------------------
add_executable(sudoku_solver
    src/main.cpp
    src/SudokuSolver.cpp
)

# ---- Test executable ------------------------------------------------------
add_executable(test_solver
    tests/test_solver.cpp
    src/SudokuSolver.cpp
)

enable_testing()
add_test(NAME SudokuTests COMMAND test_solver)
