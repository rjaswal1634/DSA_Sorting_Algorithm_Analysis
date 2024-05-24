// Created by rjasw on 4/18/2024.
// Rahul Chaudhari
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

/**
This function generates a random integer between a specified minimum and maximum value (inclusive).
@param min The minimum value (inclusive) for the generated random number.
@param max The maximum value (inclusive) for the generated random number.
@return A random integer within the range [min, max].
*/
int random_value(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Insert
// using the int method so that it will return me the steps
/**
 * This function implements the insertion sort algorithm to sort a vector of integers in ascending order.
 * @param unsorted The vector containing the unsorted elements.
 * @return The total number of steps  performed during sorting.
 */
unsigned long long int insertion_sort(vector<int> &unsorted) {
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

// Heap
/**
 * This function performs the percolate down operation
 * @param heaped_array The vector representing the heap structure.
 * @param size The size of the heap (number of elements in the vector).
 * @param parent The index of the parent node in the heap.
 * @param step_counter A reference to an unsinged long long integer variable that keeps track of the number of steps
 *
 */
void percolateDown(vector<int> &heaped_array, const int size, int parent, unsigned long long int &step_counter) {
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
 * This function iteratively calls the percolateDown function starting from the non-leaf nodes (parents)
    *towards the root to ensure the max-heap property for the entire array.
 */
unsigned long long int buildHeap(vector<int> &arr) {
    unsigned long long int step_counter = 0;
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
                step_counter++;
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
unsigned long long int heap_sort(vector<int> &unsorted) {
    unsigned long long int step_counter = buildHeap(unsorted);;
    // Use Floyd's algorithm // to Build heap (rearrange array)
    /* For Degugging Propose Use this loop to see contains of heap

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


// Quick
/**
 * This function partitions a sub-array of a vector around a chosen pivot element during the quick sort algorithm.
 *
 * @param unsorted The vector containing the unsorted elements.
 * @param start The starting index of the sub-array to be partitioned.
 * @param end The ending index of the sub-array to be partitioned.
 * @param step_counter A reference to an unsinged long long integer variable that keeps track of the number of steps.
 * @return The index of the pivot element in its final sorted position.
 */
int partition(vector<int> &unsorted, int start, int end, unsigned long long int &step_counter) {
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
 * @param step_counter A reference to an unsinged long long integer variable that keeps track of the number of steps.
 */
void quick_sort(vector<int> &unsorted, int start, int end, unsigned long long int &step_counter) {
    // base case
    if (start >= end) {
        return;
    }
    int pivot = partition(unsorted, start, end, step_counter);
    quick_sort(unsorted, start, pivot - 1, step_counter);
    quick_sort(unsorted, pivot + 1, end, step_counter);
}

// Merge
/**
 * This function merges two sorted sub-arrays of a vector into a single sorted sub-array.
 *
 * @param unsorted The vector containing the unsorted elements.
 * @param left The starting index of the first sub-array.
 * @param mid The middle index separating the two sub-arrays.
 * @param right The ending index of the second sub-array.
 * @param step_counter A reference to an unsigned long long integer variable that keeps track of the number of steps.
 *
 */
void merge(vector<int> &unsorted, int const left, int const mid, int const right,
           unsigned long long int &step_counter) {
    int const len_array_one = mid - left + 1;
    int const len_array_two = right - mid;

    vector<int> left_array(len_array_one);
    vector<int> right_array(len_array_two);

    // Copy data to temp vectors leftArray<> and rightArray<>
    for (int i = 0; i < len_array_one; i++) {
        step_counter++;
        left_array.at(i) = unsorted.at(left + i);
    }
    //step
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
 * @param step_counter A reference to an unsinged long long integer variable that keeps track of the number of steps.
 *
 */
void merge_sort(vector<int> &unsorted, int const begin, int const end, unsigned long long int &step_counter) {
    if (begin >= end)
        return;
    int mid = begin + (end - begin) / 2;
    step_counter++;
    merge_sort(unsorted, begin, mid, step_counter);
    merge_sort(unsorted, mid + 1, end, step_counter);
    merge(unsorted, begin, mid, end, step_counter);
}

int main() {
    const long SIMUL_SIZE = 10000;

    cout << "----------------------------------" << endl;
    // numbers of values that will go into vectors during sulumations
    vector<int> input_sizes{1000, 5000, 10000, 15000, 20000};

    // Use current time as seed for random generator
    srand(time(0));


    for (int i = 0; i < input_sizes.size(); i++) {
        int N = input_sizes.at(i); // taking different input sizes
        unsigned long long int insert_sort_step_asc = 0;
        unsigned long long int insert_step_count_ran = 0;
        unsigned long long int insert_step_count_des = 0;
        // main simulation loop;
        for (int simul_index = 0; simul_index < SIMUL_SIZE; simul_index++) {
            vector<int> array;
            vector<int> array_random;
            vector<int> array_descending;

            // filling the vector with randoms values
            for (int array_index = 0; array_index < N; array_index++) {
                int values = random_value(0, N);
                array.push_back(values);
                array_random.push_back(values);
                array_descending.push_back(values);
            }
            // arranging elements in sorted order
            sort(array.begin(), array.end());

            // Using sorting algorithms for ascending
            insert_sort_step_asc += insertion_sort(array);

            // Using sorting alogrith for random array

            insert_step_count_ran += insertion_sort(array_random);
            // arranging elements in  reverse sorted order
            sort(array_descending.begin(), array_descending.end(), greater<int>());
            insert_step_count_des += insertion_sort(array_descending);
        }
        // arranging already sorted elements in ascending order

        unsigned long long int average_steps_insert_asc = insert_sort_step_asc / SIMUL_SIZE;
        unsigned long long int average_steps_insert_des = insert_step_count_des / SIMUL_SIZE;
        unsigned long long int average_steps_insert_ran = insert_step_count_ran / SIMUL_SIZE;

        cout << "Input Size (N): " << N << endl;

        cout << "Average Number of Steps Insert(Ase): " << average_steps_insert_asc << endl;
        cout << "Average Number of Steps Insert(Ran): " << average_steps_insert_ran << endl;
        cout << "Average Number of Steps Insert(des): " << average_steps_insert_des << endl;
        cout << "----------------------------------" << endl;
    }

    return 0;
}

/* //Merge Sort Main Method
 * int main() {
    const long SIMUL_SIZE = 10000;

    cout << "----------------------------------" << endl;
    // numbers of values that will go into vectors during sulumations
    vector<int> input_sizes{1000, 5000, 10000, 15000, 20000};

    // Use current time as seed for random generator
    srand(time(0));

    // This loop will run 6 times for different values above from 10K to 100K
    for (int i = 0; i < input_sizes.size(); i++) {
        int N = input_sizes.at(i); // taking different input sizes
        unsigned long long int merge_step_count_asc = 0;
        unsigned long long int merge_step_count_ran = 0;
        unsigned long long int merge_step_count_des = 0;
        // main simulation loop;
        for (int simul_index = 0; simul_index < SIMUL_SIZE; simul_index++) {
            vector<int> array;
            vector<int> array_random;
            vector<int> array_descending;

            // filling the vector with randoms values
            for (int array_index = 0; array_index < N; array_index++) {
                int values = random_value(0, N);
                array.push_back(values);
                array_random.push_back(values);
                array_descending.push_back(values);
            }
            // arranging elements in sorted order
            sort(array.begin(), array.end());

            // Using sorting algorithms for ascending
            merge_sort(array, 0, array.size() - 1, merge_step_count_asc);

            // Using sorting alogrith for random array
            merge_sort(array_random, 0, array_random.size() - 1, merge_step_count_ran);

            // arranging elements in  reverse sorted order
            sort(array_descending.begin(), array_descending.end(), greater<int>());
            merge_sort(array_descending, 0, array_descending.size() - 1, merge_step_count_des);

        }
        // arranging already sorted elements in ascending order

        unsigned long long int average_steps_merge_asc = merge_step_count_asc / SIMUL_SIZE;
        unsigned long long int average_steps_merge_des = merge_step_count_des / SIMUL_SIZE;
        unsigned long long int average_steps_merge_ran = merge_step_count_ran / SIMUL_SIZE;

        cout << "Input Size (N): " << N << endl;

        cout << "Average Number of Steps Merge(Ase): " << average_steps_merge_asc << endl;
        cout << "Average Number of Steps Merge(des): " << average_steps_merge_des << endl;
        cout << "Average Number of Steps Merge(des): " << average_steps_merge_ran << endl;
        cout << "----------------------------------" << endl;
    }

    return 0;
}
 */

/* //Quick Sort Main method
 *nt main() {
    const long SIMUL_SIZE = 10000;

    cout << "----------------------------------" << endl;
    // numbers of values that will go into vectors during sulumations
    vector<int> input_sizes{1000, 5000, 10000, 15000, 20000};

    // Use current time as seed for random generator
    srand(time(0));

    // This loop will run 6 times for different values above from 10K to 100K
    for (int i = 0; i < input_sizes.size(); i++) {
        int N = input_sizes.at(i); // taking different input sizes
        unsigned long long int quick_sort_step_asc = 0;
        unsigned long long int quick_step_count_ran = 0;
        unsigned long long int quick_step_count_des = 0;
        // main simulation loop;
        for (int simul_index = 0; simul_index < SIMUL_SIZE; simul_index++) {
            vector<int> array;
            vector<int> array_random;
            vector<int> array_descending;

            // filling the vector with randoms values
            for (int array_index = 0; array_index < N; array_index++) {
                int values = random_value(0, N);
                array.push_back(values);
                array_random.push_back(values);
                array_descending.push_back(values);
            }

            // arranging elements in sorted order
            sort(array.begin(), array.end());

            // Using sorting algorithms for ascending
            quick_sort(array, 0, array.size() - 1, quick_sort_step_asc);

            //using it for random values
            quick_sort(array_random, 0, array_random.size() - 1, quick_step_count_ran);

            // Sorting it in desending order
            sort(array_descending.begin(), array_descending.end(), greater<int>());
            quick_sort(array_descending, 0, array_descending.size() - 1, quick_step_count_des);
        }

        unsigned long long int average_steps_quick_asc = quick_sort_step_asc / SIMUL_SIZE;
        unsigned long long int average_steps_quick_des = quick_step_count_des / SIMUL_SIZE;
        unsigned long long int average_steps_quick_ran = quick_step_count_ran / SIMUL_SIZE;

        cout << "Input Size (N): " << N << endl;

        cout << "Average Number of Steps Quick(Ase): " << average_steps_quick_asc << endl;
        cout << "Average Number of Steps Quick(Ran): " << average_steps_quick_ran << endl;
        cout << "Average Number of Steps Quick(des): " << average_steps_quick_des << endl;
        cout << "----------------------------------" << endl;
    }
    return 0;
}
 **/

/* //Heap Sort Main method
 *int main() {
    const long SIMUL_SIZE = 10000;

    cout << "----------------------------------" << endl;
    // numbers of values that will go into vectors during sulumations
    vector<int> input_sizes{1000, 5000, 10000, 15000, 20000};

    // Use current time as seed for random generator
    srand(time(0));

    // This loop will run 6 times for different values above from 10K to 100K
    for (int i = 0; i < input_sizes.size(); i++) {
        int N = input_sizes.at(i); // taking different input sizes
        unsigned long long int heap_sort_step_asc = 0;
        unsigned long long int heap_step_count_ran = 0;
        unsigned long long int heap_step_count_des = 0;
        // main simulation loop;
        for (int simul_index = 0; simul_index < SIMUL_SIZE; simul_index++) {
            vector<int> array;
            vector<int> array_random;
            vector<int> array_descending;

            // filling the vector with randoms values
            for (int array_index = 0; array_index < N; array_index++) {
                int values = random_value(0, N);
                array.push_back(values);
                array_random.push_back(values);
                array_descending.push_back(values);
            }
            // arranging elements in sorted order
            sort(array.begin(), array.end());

            // Using sorting algorithms for ascending
            heap_sort_step_asc += heap_sort(array);

            // Using sorting alogrith for random array

            heap_step_count_ran += heap_sort(array_random);
            // arranging elements in  reverse sorted order
            sort(array_descending.begin(), array_descending.end(), greater<int>());
            heap_step_count_des += heap_sort(array_descending);

        }
        // arranging already sorted elements in ascending order

        unsigned long long int average_steps_heap_asc = heap_sort_step_asc / SIMUL_SIZE;
        unsigned long long int average_steps_heap_des = heap_step_count_des / SIMUL_SIZE;
        unsigned long long int average_steps_heap_ran = heap_step_count_ran / SIMUL_SIZE;

        cout << "Input Size (N): " << N << endl;

        cout << "Average Number of Steps heap(Ase): " << average_steps_heap_asc << endl;
        cout << "Average Number of Steps heap(Ran): " << average_steps_heap_ran << endl;
        cout << "Average Number of Steps heap(des): " << average_steps_heap_des << endl;
        cout << "----------------------------------" << endl;
    }

    return 0;
}
 */
