# Matrix Multiplication — Loop Ordering, Data Locality and Cache Behaviour

A C++ project implementing dense matrix–matrix multiplication (`C = A × B`) in all six loop orderings, used to experimentally study the effect of loop order on performance and to infer cache hierarchy properties (Experiment 1: Loop Ordering, Data Locality and Cache Behaviour).

## What it does

- Implements all six loop orderings — `ijk`, `ikj`, `jik`, `jki`, `kij`, `kji` — each in its own header/source file.
- **Part A**: compares all six orderings at a fixed matrix size N, measuring execution time and GFLOP/s, verifying correctness against the `ijk` reference, and reporting the predicted memory-access pattern (stride-1 / stride-N / fixed) for each array in the innermost loop.
- **Part B**: takes the fastest ordering (`ikj`) and sweeps N across powers of 2, recording execution time, GFLOP/s, memory footprint, and the ratio `T(N)/T(N/2)` — used to detect where the working set stops fitting in a given cache level.
- **Follow-up stride experiment**: walks a large array with increasing strides to estimate the cache line length from where per-access latency plateaus.
- A general-purpose comparison tool (`MatrixMultiplication`) for quick one-off runs of all six orderings at any N.

## Project Structure

```text
MatrixMultiplication/
│
├── CMakeLists.txt
│
├── include/
│   ├── MatMulIJK.h
│   ├── MatMulIKJ.h
│   ├── MatMulJIK.h
│   ├── MatMulJKI.h
│   ├── MatMulKIJ.h
│   └── MatMulKJI.h
│
├── src/
│   ├── MatMulIJK.cpp
│   ├── MatMulIKJ.cpp
│   ├── MatMulJIK.cpp
│   ├── MatMulJKI.cpp
│   ├── MatMulKIJ.cpp
│   ├── MatMulKJI.cpp
│   ├── main.cpp              # general-purpose comparison (all 6 orderings, one run)
│   ├── partA.cpp              # Table A — loop-order comparison at fixed N
│   ├── partB.cpp               # Table B — cache sweep across powers of 2
│   └── strideExperiment.cpp    # follow-up cache-line-length probe
│
└── output/
    ├── comparison_report.txt   # written by MatrixMultiplication
    ├── table_A.txt             # written by PartA
    ├── table_B.txt             # written by PartB
    └── stride_experiment.txt   # written by StrideExperiment
```

| Path | Purpose |
|---|---|
| `include/*.h` | Function declaration for one loop ordering each. |
| `src/*Sort.cpp`... `src/MatMul*.cpp` | Implementation of each loop ordering, operating on flattened `std::vector<double>` matrices (row-major). |
| `src/main.cpp` | Quick all-six comparison at a configurable N. |
| `src/partA.cpp` | Generates Table A: per-ordering timing, GFLOP/s, correctness, predicted access pattern, ranking. |
| `src/partB.cpp` | Generates Table B: cache-sweep timing, footprint, GFLOP/s, `T(N)/T(N/2)` ratio. |
| `src/strideExperiment.cpp` | Generates the stride-vs-latency table for estimating cache line size. |
| `CMakeLists.txt` | Build configuration for all four executables. |

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

This produces four executables inside `build/`:

- **`MatrixMultiplication`** — general-purpose comparison tool.
- **`PartA`** — loop-order investigation (Table A).
- **`PartB`** — cache investigation (Table B).
- **`StrideExperiment`** — follow-up stride/cache-line experiment.

## Running

All programs write their report to `output/`, relative to the project root (i.e. run from inside `build/`).

### Part A — loop-order comparison

```bash
./PartA [N] [REPEATS]
```

- `N` — matrix dimension (default `1024`)
- `REPEATS` — timed runs per ordering, best time kept (default `10`)

```bash
./PartA 1024 10
```

Writes `output/table_A.txt`: execution time, GFLOP/s, correctness vs. the `ijk` reference, predicted access pattern per array, and rank, for each of the six orderings — plus a grouping by innermost loop index.

⚠️ At N = 2048 with 10 repeats × 6 orderings, this can take a long time, especially for the cache-unfriendly `jki`/`kji` orders. Try a smaller N first (e.g. `./PartA 512 3`) to sanity-check before running the full size.

### Part B — cache investigation

```bash
./PartB [MAX_N] [REPEATS]
```

- `MAX_N` — largest N to test, must be a power of 2 (default `2048`)
- `REPEATS` — timed runs per size, best time kept (default `5`)

```bash
./PartB 2048 5
```

Writes `output/table_B.txt`: for each N = 32, 64, 128, ..., `MAX_N` — memory footprint (`3N²×8` bytes), execution time, GFLOP/s, and the ratio `T(N)/T(N/2)`. Since operation count grows exactly 8× when N doubles, a ratio noticeably above 8 (or a drop in GFLOP/s) marks where the working set stops fitting in a cache level.

### Follow-up stride experiment

```bash
./StrideExperiment [ACCESSES]
```

- `ACCESSES` — number of memory accesses timed per stride (default `20000000`)

```bash
./StrideExperiment 20000000
```

Writes `output/stride_experiment.txt`: average time per access (ns) for strides from 8 to 4096 bytes, over a 256 MB array (larger than any cache level). The stride at which the delta between successive rows flattens out estimates the cache line length.

### General comparison tool

```bash
./MatrixMultiplication [N]
```

Runs all six orderings once each at the given N (default `2500`) and writes `output/comparison_report.txt` with timings and the fastest ordering.

## Interpreting the results

- **Table A**: `ikj` and `kij` should be fastest — both sweep `A` (or hold it fixed) and `B`/`C` with stride-1 access in the innermost loop. `jki`/`kji` should be slowest, with stride-N access on two of the three arrays. `ijk`/`jik` fall in between.
- **Table B**: watch the `T(N)/T(N/2)` column. It should hover near 8 while the matrices fit comfortably in cache, then jump noticeably higher once the memory footprint (`3N²×8` bytes) exceeds a cache level's capacity.
- **Stride experiment**: ns/access should rise as stride increases from small values, then flatten once stride ≥ cache line size. The flattening point is your estimated line length (commonly 64 bytes on x86).

## Notes

- All matrices are `double`, initialized with reproducible pseudo-random values (fixed seeds).
- Correctness in Part A is checked against the `ijk` reference with a small floating-point tolerance (all six orderings accumulate `k` in the same order, so results should match almost exactly).
- Record your compiler version and optimization flags used (`-O2` by default, set in `CMakeLists.txt`) in your lab report — the sheet asks for this explicitly.
- Generate `tree.txt` from the project root after building, as required by the lab sheet:
  ```bash
  find . -print | sed -e 's;[^/]*/;|____;g;s;____|; |;g' > tree.txt
  ```

## Extending

To add a plotting step (GFLOP/s vs. loop ordering, GFLOP/s vs. log₂N as required by the sheet), parse `table_A.txt` / `table_B.txt` with a small Python/gnuplot script and save the charts alongside `output/`.
