#include <iostream>
#include <vector>
#include <cassert>

#include "BubbleSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"

using namespace std;

bool isSorted(const vector<int>& arr)
{
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[i - 1])
            return false;
    }

    return true;
}

int main()
{
    vector<int> original = {9, 5, 1, 7, 3, 8, 2, 6, 4};

    vector<int> bubble = original;
    vector<int> merge = original;
    vector<int> quick = original;

    bubbleSort(bubble);
    mergeSort(merge);
    quickSort(quick);

    assert(isSorted(bubble));
    assert(isSorted(merge));
    assert(isSorted(quick));

    cout << "All sorting algorithms passed the test successfully.\n";

    return 0;
}