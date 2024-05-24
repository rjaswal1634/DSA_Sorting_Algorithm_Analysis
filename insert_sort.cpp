// Created by rjasw on 4/18/2024.
// Rahul Chaudhari
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// using the int method so that it will return me the steps
/**
 * This function implements the insertion sort algorithm to sort a vector of integers in ascending order.
 * @param unsorted The vector containing the unsorted elements.
 * @return The total number of steps  performed during sorting.
 */
int insertion_sort(vector<int> &unsorted) {
    size_t array_size = unsorted.size();
    int step_counter = 0;
    for (int i = 1; i < array_size; i++) {
        int key = unsorted[i];
        int j = i - 1;
        step_counter++;
        while (j >= 0 && unsorted[j] > key) {
            unsorted[j + 1] = unsorted[j];
            j = j - 1;
            step_counter++;
        }
        unsorted[j + 1] = key;
    }
    return step_counter;
}

int main() {
    vector<int> array{500, 10, 6, 200, 70, 60, 40, 100, 30, 300, 400, 150};
    cout << "\nPrinting the Input Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    int steps = insertion_sort(array);
    cout << "\nPrinting the Sorted Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    cout << "\nTOTAL STEPS for Insertion Sort: " << steps << endl;
    return 0;
}
