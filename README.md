# sudokuSolver

A small C++ project implementing a backtracking Sudoku solver.

## Structure

- `src/` — source files:
  - `SudokuSolver.h` / `SudokuSolver.cpp` — solver implementation and helpers
  - `main.cpp` — CLI to read a puzzle and print the solution
- `puzzles/` — sample puzzles (`example.txt`)
- `tests/` — simple test executable (no external test framework)
- `CMakeLists.txt` — build configuration

## Build (Linux / macOS / Windows with CMake)

1. Create build dir:
   ```
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

2. Run solver:
   - From build dir:
     ```
     ./sudoku_solver ../puzzles/example.txt
     ```
     Or run interactively:
     ```
     ./sudoku_solver
     ```

3. Run tests:
   ```
   ./test_solver
   ```

## Input format

Nine lines, each containing nine characters: digits `1`..`9` or `.` for empty cells. Example:

```
53..7....
6..195...
.98....6.
8...6...3
4..8.3..1
7...2...6
.6....28.
...419..5
....8..79
```

## Notes & next steps

- This project uses a straightforward backtracking solver (depth-first). It's fast for typical puzzles but can be further optimized by:
  - Choosing the next empty cell with minimum remaining candidates (MRV heuristic).
  - Maintaining row/col/box bitsets to test candidate validity in O(1).
  - Adding a CLI option to print steps or count backtracks.
- You can add a GUI (Qt) or Web front-end (Emscripten) if desired.

## License

MIT — use as you wish.
