# SortingComparison

A C++ project that compares the performance of three classic sorting algorithms — **Bubble Sort**, **Merge Sort**, and **Quick Sort** — across a range of input sizes, and verifies their correctness independently of performance.

## What it does

- Generates random integer arrays at several sizes (100 to 20,000 elements).
- Sorts identical copies of each array with all three algorithms.
- Measures execution time using `<chrono>`, averaged over multiple runs per size to reduce noise.
- Writes a full performance report to `output/comparison_report.txt`, including a per-size breakdown and an overall summary of which algorithm was fastest.
- Separately verifies correctness of all three algorithms at each input size via a dedicated test program.

## Project Structure

```text
SortingComparison/
│
├── CMakeLists.txt
│
├── include/
│   ├── BubbleSort.h
│   ├── MergeSort.h
│   └── QuickSort.h
│
├── src/
│   ├── BubbleSort.cpp
│   ├── MergeSort.cpp
│   ├── QuickSort.cpp
│   └── main.cpp
│
├── test/
│   └── test.cpp
│
├── output/
│   └── comparison_report.txt
│
└── build/
```

| Path | Purpose |
|---|---|
| `include/*.h` | Function declarations for each sorting algorithm. |
| `src/*Sort.cpp` | Implementation of each sorting algorithm. |
| `src/main.cpp` | Runs the performance comparison and writes the report. |
| `test/test.cpp` | Verifies correctness of all three algorithms at each input size. |
| `output/comparison_report.txt` | Generated performance report (created when `main.cpp` runs). |
| `CMakeLists.txt` | Build configuration for CMake. |

## Requirements

- A C++17-capable compiler (e.g. `g++`, `clang++`)
- CMake 3.10 or later

## Building

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

This produces two executables inside `build/`:

- **`SortingComparison`** — runs the performance comparison.
- **`RunTests`** — runs the correctness tests.

## Running

From inside the `build/` directory:

```bash
./SortingComparison
```

This generates `output/comparison_report.txt` containing execution times for each algorithm at each input size, plus an overall summary.

```bash
./RunTests
```

This prints a PASS/FAIL result for each input size and a final summary line. It exits with status `0` if every size passed, or `1` if any failed — so it can be used in a CI pipeline.

## Configuration

Both `main.cpp` and `test.cpp` define the input sizes they use near the top of the file:

```cpp
const std::vector<size_t> INPUT_SIZES = {100, 500, 1000, 5000, 10000, 20000};  // main.cpp
const std::vector<size_t> TEST_SIZES  = {0, 1, 100, 500, 1000, 5000, 10000, 20000}; // test.cpp
```

`main.cpp` also defines how many times each size is repeated and averaged:

```cpp
const int RUNS_PER_SIZE = 5;
```

Adjust these values to test different sizes or repetition counts.

## Sample Report Output

```text
===================================================
        SORTING ALGORITHM PERFORMANCE REPORT
===================================================

Input Size : 100

Bubble Sort : 25 microseconds
Merge Sort  : 11 microseconds
Quick Sort  : 3 microseconds

Best Algorithm : Quick Sort
Correctness    : PASSED

---------------------------------------------------
...
===================================================

OVERALL SUMMARY

Fastest Overall

Quick Sort

Observations

* Bubble Sort execution time increases rapidly as input size grows.
* Merge Sort maintains O(n log n) performance.
* Quick Sort provides the best average execution time for random data.
===================================================
```

## Notes

- Each algorithm sorts its **own copy** of the same randomly generated array at each run, ensuring a fair, apples-to-apples comparison.
- Random data is generated with a fixed seed per size/run combination, so results are reproducible across runs on the same machine.
- Bubble Sort's O(n²) behavior becomes very visible at larger sizes (20,000 elements can take over a second), while Merge Sort and Quick Sort stay in the microsecond-to-low-millisecond range thanks to their O(n log n) average performance.

## Extending

To add another algorithm (e.g. Heap Sort):

1. Add `HeapSort.h` to `include/` and `HeapSort.cpp` to `src/`.
2. Add the new source file to both executables in `CMakeLists.txt`.
3. Call the new function from `main.cpp` and `test.cpp` alongside the existing three.
