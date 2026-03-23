# Flower Exchange

A C++17 flower exchange matching engine.

## Prerequisites

- C++ compiler with C++17 support (`g++`/`clang++`)
- `make` (for Makefile workflow)
- `cmake` (for CMake workflow)

## Project Layout

- `CMakeLists.txt` : CMake build configuration
- `Makefile` : Make build configuration
- `order.csv` : Input orders
- `src/` : Source code (app/domain/validation/interfaces/io/services)
- `output/` : Generated CSV files
  - `output/execution_reps/`
  - `output/order_books/`
  - `output/rejected_execution_reps/`

## Build and Run (Make)

From the project root:

```bash
make clean
make
make run
```

This builds `ExchangeAppMain` and runs it.

## Build and Run (CMake)

From the project root:

```bash
cmake -S . -B build
cmake --build build
./build/ExchangeAppMain
```

## Input File

- The app reads orders from `order.csv` in the project root.

## Output Files

When you run the app, CSV files are generated here:

- Execution reports: `output/execution_reps/`
- Order books: `output/order_books/`
- Rejected reports: `output/rejected_execution_reps/`

## Notes

- The app performs output cleanup before each run.
- Ensure `order.csv` exists before running.
