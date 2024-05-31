#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    void* temp = v[i];
    v[i] = v[j];
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
    int i, last;

    /**
     * Base case: if the sub-array has fewer than two elements, return.
     */
    if (left >= right) return;

    /**
     * Move the pivot element to the start of the sub-array.
     */
    swap(v, left, (left + right) / 2);

    last = left;
    
    /**
     * Partition the array into elements less than and greater than the pivot.
     */
    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0)
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
 * Comparison function for case-insensitive string comparison.
 *
 * @param a First string.
 * @param b Second string.
 * @return Negative value if a < b, zero if a == b, positive value if a > b.
 */
int case_insensitive_strcmp(void* a, void* b) {
    #ifdef _WIN32
        return _stricmp((char*)a, (char*)b);
    #else
        return strcasecmp((char*)a, (char*)b);
    #endif
}

/**
 * Main function to demonstrate the case-insensitive sorting of names.
 */
void main(void) {
    /**
     * Sort the names array using generic_qsort with case_insensitive_strcmp.
     */
    generic_qsort((void**)names, 0, 11, case_insensitive_strcmp);

    /**
     * Print the sorted names.
     */
    for (int i = 0; i < 12; i++)
        printf("%s\n", names[i]);
}

