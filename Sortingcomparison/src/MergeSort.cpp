#include "MergeSort.hpp"

namespace {

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i] <= rightPart[j]) {
            arr[k++] = leftPart[i++];
        } else {
            arr[k++] = rightPart[j++];
        }
    }

    while (i < leftPart.size()) {
        arr[k++] = leftPart[i++];
    }

    while (j < rightPart.size()) {
        arr[k++] = rightPart[j++];
    }
}

void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

} // namespace

void mergeSort(std::vector<int>& arr) {
    if (arr.empty()) {
        return;
    }
    mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
}