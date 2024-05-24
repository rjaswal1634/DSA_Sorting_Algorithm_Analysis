#include <iostream>
#include <vector>
using namespace std;

/**
 * This function partitions a sub-array of a vector around a chosen pivot element during the quick sort algorithm.
 *
 * @param unsorted The vector containing the unsorted elements.
 * @param start The starting index of the sub-array to be partitioned.
 * @param end The ending index of the sub-array to be partitioned.
 * @param step_counter A reference to an integer variable that keeps track of the number of steps.
 * @return The index of the pivot element in its final sorted position.
 */
int partition(vector<int> &unsorted, int start, int end, int &step_counter) {
    int pivot = unsorted.at(start);
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (unsorted.at(i) <= pivot) {
            count++;
        }
        step_counter++;
    }
    int pivotIndex = start + count;
    // Put the split value in the 'middle'
    swap(unsorted.at(pivotIndex), unsorted.at(start));
    step_counter++;
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex) {
        while (unsorted.at(i) <= pivot) {
            i++;
            step_counter++;
        }
        while (unsorted.at(j) > pivot) {
            j--;
            step_counter++;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(unsorted.at(i++), unsorted.at(j--));
            step_counter++;
        }
    }
    return pivotIndex;
}

/**
 * This function implements the quicksort algorithm to sort a vector of integers in ascending order.
 * @param unsorted The vector containing the unsorted elements.
 * @param start The starting index of the sub-array to be sorted.
 * @param end The ending index of the sub-array to be sorted.
 * @param step_counter A reference to an integer variable that keeps track of the number of steps.
 */
void quick_sort(vector<int> &unsorted, int start, int end, int &step_counter) {
    // base case
    if (start >= end) {
        return;
    }
    int pivot = partition(unsorted, start, end, step_counter);
    quick_sort(unsorted, start, pivot - 1, step_counter);
    quick_sort(unsorted, pivot + 1, end, step_counter);
}


int main() {
    vector<int> array{500, 10, 6, 200, 70, 60, 40, 100, 30, 300, 400, 150};
    cout << "\nPrinting the Input Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    int steps = 0;
    quick_sort(array, 0, array.size() - 1, steps);
    cout << "\nPrinting the Sorted Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    cout << "\nTOTAL STEPS for Quick Sort: " << steps << endl;
    return 0;
}
