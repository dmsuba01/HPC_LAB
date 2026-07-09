#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>

#include "BubbleSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"

using namespace std;
using namespace chrono;

// Generate random array
vector<int> generateRandomArray(int size)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);

    vector<int> arr(size);

    for (int &x : arr)
        x = dis(gen);

    return arr;
}

int main()
{
    vector<int> inputSizes = {100, 500, 1000, 5000, 10000};

    ofstream report("../output/comparison_report.txt");

    if (!report)
    {
        cout << "Unable to create report file.\n";
        return 1;
    }

    report << "=========================================\n";
    report << "SORTING ALGORITHM PERFORMANCE REPORT\n";
    report << "=========================================\n\n";

    for (int size : inputSizes)
    {
        vector<int> original = generateRandomArray(size);

        vector<int> bubble = original;
        vector<int> merge = original;
        vector<int> quick = original;

        // Bubble Sort
        auto start = high_resolution_clock::now();
        bubbleSort(bubble);
        auto end = high_resolution_clock::now();

        auto bubbleTime =
            duration_cast<microseconds>(end - start).count();

        // Merge Sort
        start = high_resolution_clock::now();
        mergeSort(merge);
        end = high_resolution_clock::now();

        auto mergeTime =
            duration_cast<microseconds>(end - start).count();

        // Quick Sort
        start = high_resolution_clock::now();
        quickSort(quick);
        end = high_resolution_clock::now();

        auto quickTime =
            duration_cast<microseconds>(end - start).count();

        string bestAlgorithm = "Bubble Sort";
        long long bestTime = bubbleTime;

        if (mergeTime < bestTime)
        {
            bestTime = mergeTime;
            bestAlgorithm = "Merge Sort";
        }

        if (quickTime < bestTime)
        {
            bestTime = quickTime;
            bestAlgorithm = "Quick Sort";
        }

        report << "Input Size : " << size << "\n\n";

        report << "Bubble Sort : "
               << bubbleTime
               << " microseconds\n";

        report << "Merge Sort  : "
               << mergeTime
               << " microseconds\n";

        report << "Quick Sort  : "
               << quickTime
               << " microseconds\n\n";

        report << "Best Algorithm : "
               << bestAlgorithm << "\n";

        report << "-----------------------------------------\n\n";

        cout << "Completed test for input size "
             << size << endl;
    }

    report.close();

    cout << "\nComparison report generated successfully.\n";

    return 0;
}