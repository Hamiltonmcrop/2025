#include <stdio.h>
#include <string.h>

/**
 * Array of names to be sorted.
 */
char* names[] = {
    "kiwi", "berries", "apple", "orange", "strawberry", "pineapple",
    "Kiwi", "Berries", "Apple", "Orange", "Strawberry", "Pineapple"
};

/**
 * Swaps two elements in an array.
 *
 * @param v Array of pointers.
 * @param i Index of the first element.
 * @param j Index of the second element.
 */
void swap(void* v[], int i, int j) {
    /**
     * Store the element at index i in a temporary variable.
     */
    void* temp = v[i];
    /**
     * Assign the element at index j to index i.
     */
    v[i] = v[j];
    /**
     * Assign the temporary variable to index j.
     */
    v[j] = temp;
}

/**
 * Quicksort algorithm for sorting an array of pointers.
 *
 * @param v Array of pointers.
 * @param left Left index of the sub-array to sort.
 * @param right Right index of the sub-array to sort.
 * @param comp Comparison function to determine the order.
 */
void generic_qsort(void* v[], int left, int right, int(*comp)(void*, void*)) {
    /**
     * Define variables for the current index and the last position of the pivot.
     */
    int i, last;

    /**
     * Base case: if the sub-array has fewer than two elements, return.
     */
    if (left >= right) return;

    /**
     * Move the pivot element to the start of the sub-array.
     */
    swap(v, left, (left + right) / 2);

    /**
     * Initialize last to the left index.
     */
    last = left;

    /**
     * Partition the array into elements less than and greater than the pivot.
     */
    for (i = left + 1; i <= right; i++) {
        /**
         * If the current element is greater than the pivot (for descending order),
         * swap it with the element at index last + 1 and increment last.
         */
        if ((*comp)(v[i], v[left]) > 0)
            swap(v, ++last, i);
    }

    /**
     * Restore the pivot element to its correct position.
     */
    swap(v, left, last);

    /**
     * Recursively sort the sub-arrays.
     */
    generic_qsort(v, left, last - 1, comp);
    generic_qsort(v, last + 1, right, comp);
}

/**
 * Comparison function for descending order.
 *
 * @param a First string.
 * @param b Second string.
 * @return Negative value if a > b, zero if a == b, positive value if a < b.
 */
int reverse_strcmp(void* a, void* b) {
    /**
     * Return the result of comparing b to a using strcmp for descending order.
     */
    return strcmp((char*)b, (char*)a);
}

/**
 * Main function to demonstrate the sorting of names in descending order.
 */
void main(void) {
    /**
     * Sort the names array using generic_qsort with reverse_strcmp.
     */
    generic_qsort((void**)names, 0, 11, reverse_strcmp);

    /**
     * Print the sorted names.
     */
    for (int i = 0; i < 12; i++)
        printf("%s\n", names[i]);
}

