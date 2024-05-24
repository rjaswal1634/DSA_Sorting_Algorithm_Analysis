//
// Created by rjasw on 4/18/2024.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * This function performs the percolate down operation
 * @param heaped_array The vector representing the heap structure.
 * @param size The size of the heap (number of elements in the vector).
 * @param parent The index of the parent node in the heap.
 * @param step_counter A reference to an integer variable that keeps track of the number of steps
 *
 */
void percolateDown(vector<int> &heaped_array, const int size, int parent, int &step_counter) {
    int target = 0;
    while ((2 * parent + 1) < size) {
        step_counter++;
        //at least one child
        int left = 2 * parent + 1;
        int right = left + 1;
        // find the index of the maximum child
        if (right >= size || heaped_array.at(left) > heaped_array.at(right))
            // Using .at method of vector can also use []
            target = left;
        else
            target = right;
        // determine if the swap is needed
        if (heaped_array.at(target) > heaped_array.at(parent)) {
            swap(heaped_array.at(parent), heaped_array.at(target));
            parent = target;
            step_counter++;
        } else
            break; // reorganization is complete
    }
}

/**
 * This function builds a max-heap from a given unsorted vector using Floyd's algorithm.
 * @param arr The vector containing the unsorted elements.
 * @return The total number of steps (comparisons) performed during heap construction.
 *
 * This function iteratively calls the percolateDown function starting from the non-leaf nodes (parents)
*	towards the root to ensure the max-heap property for the entire array.
 */
int buildHeap(vector<int> &arr) {
    int step_counter = 0;
    // Using Floyd's Algorithm
    size_t size = arr.size();
    for (int i = ((size - 1) / 2); i >= 0; i--) {
        int val = arr.at(i);
        int hole = i;
        int target = 0;
        // Using Customized Percualte Down Function Cuz it need to compare with Val
        while (2 * hole + 1 < size) {
            step_counter++;
            int left = 2 * hole + 1;
            int right = left + 1;
            if (right >= size || arr.at(left) > arr.at(right)) {
                target = left;
            } else
                target = right;
            if (arr.at(target) > val) {
                arr.at(hole) = arr.at(target);
                hole = target;
            } else {
                break;
            }
        }
        arr.at(hole) = val;
    }
    return step_counter;
}

/**
 * This function sorts a vector of integers in ascending order using the heap sort algorithm.
 *
 * @param unsorted The vector containing the unsorted elements.
 * @return The total number of steps (comparisons and swaps) performed during sorting.
 *
 */
int heap_sort(vector<int> &unsorted) {
    int step_counter = buildHeap(unsorted);;

    // Use Floyd's algorithm // to Build heap (rearrange array)
    /* For Degugging Propose Use this loop to see contains of heap
     *
     for (const int num: unsorted) {
        cout << num << " ";
    }
    */

    for (int i = unsorted.size() - 1; i >= 0; i--) {
        // Move current root to end
        std::swap(unsorted.at(0), unsorted.at(i));
        step_counter++; // Increment step count for the swap operation
        // adjust the heap's new root
        percolateDown(unsorted, i, 0, step_counter);
    }
    // Output the number of steps
    return step_counter;
}


int main() {
    vector<int> array{500, 10, 6, 200, 70, 60, 40, 100, 30, 300, 400, 150};
    cout << "\nPrinting the Input Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    int steps = heap_sort(array);
    cout << "\nPrinting the Sorted Array: ";
    for (const int num: array) {
        cout << num << " ";
    }
    cout << "\nTOTAL STEPS for Heap Sort: " << steps << endl;
    return 0;
}
