#include <iostream>
#include <vector>
using namespace std;


/**
 * This function merges two sorted sub-arrays of a vector into a single sorted sub-array.
 *
 * @param unsorted The vector containing the unsorted elements.
 * @param left The starting index of the first sub-array.
 * @param mid The middle index separating the two sub-arrays.
 * @param right The ending index of the second sub-array.
 * @param step_counter A reference to an integer variable that keeps track of the number of steps.
 *
 */
void merge(vector<int> &unsorted, int const left, int const mid, int const right, int &step_counter) {
    int const len_array_one = mid - left + 1;
    int const len_array_two = right - mid;

    vector<int> left_array(len_array_one);
    vector<int> right_array(len_array_two);

    // Copy data to temp vectors leftArray<> and rightArray<>
    for (int i = 0; i < len_array_one; i++) {
        step_counter++;
        left_array.at(i) = unsorted.at(left + i);
    }
    for (int j = 0; j < len_array_two; j++) {
        step_counter++;
        right_array.at(j) = unsorted.at(mid + 1 + j);
    }
    int index_subarray_one = 0; // Initial index of first sub-array
    int index_subarray_two = 0; // Initial index of second sub-array
    int index_merged_array = left; // Initial index of the merged array

    while (index_subarray_one < len_array_one && index_subarray_two < len_array_two) {
        step_counter++;
        if (left_array.at(index_subarray_one) <= right_array.at(index_subarray_two)) {
            unsorted.at(index_merged_array) = left_array.at(index_subarray_one);
            index_subarray_one++;
        } else {
            unsorted.at(index_merged_array) = right_array.at(index_subarray_two);
            index_subarray_two++;
        }
        index_merged_array++;
    }

    // Copy the remaining elements of left_array to unsorted vector
    while (index_subarray_one < len_array_one) {
        unsorted.at(index_merged_array) = left_array.at(index_subarray_one);
        index_subarray_one++;
        index_merged_array++;
        step_counter++;
    }

    // Copy the remaining elements of right_array to unsorted vector
    while (index_subarray_two < len_array_two) {
        unsorted.at(index_merged_array) = right_array.at(index_subarray_two);
        index_subarray_two++;
        index_merged_array++;
        step_counter++;
    }
}

/**
 * This function implements the merge sort algorithm to sort a vector of integers in ascending order.
 *
 * @param unsorted The vector containing the unsorted elements.
 * @param begin The starting index of the sub-array to be sorted.
 * @param end The ending index of the sub-array to be sorted.
 * @param step_counter A reference to an integer variable that keeps track of the number of steps.
 *
 */
void merge_sort(vector<int> &unsorted, int const begin, int const end, int &step_counter) {
    if (begin >= end)
        return;
    int mid = begin + (end - begin) / 2;
    step_counter++;
    merge_sort(unsorted, begin, mid, step_counter);
    merge_sort(unsorted, mid + 1, end, step_counter);
    merge(unsorted, begin, mid, end, step_counter);
}

int main() {
    vector<int> array{500, 10, 6, 200, 70, 60, 40, 100, 30, 300, 400, 150};
    cout << "\nPrinting the Input Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    int steps = 0;
    merge_sort(array, 0, array.size() - 1, steps);
    cout << "\nPrinting the Sorted Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    cout << "\nTOTAL STEPS for Heap Sort: " << steps << endl;
    return 0;
}
