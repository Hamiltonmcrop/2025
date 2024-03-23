public class AnyTypeMergeSort<T extends Comparable<T>> {

    // Method to merge two sorted subarrays into one sorted array
    @SuppressWarnings("unchecked")
    public void merge(T[] A, int lowerBound, int midPoint, int upperBound) {
        // Calculate the lengths of the two subarrays
        int nL = midPoint - lowerBound + 1; // length of A[p:q]
        int nR = upperBound - midPoint;      // length of A[q+1:r]

        // Create arrays to store the left and right subarrays
        Object[] L = new Object[nL];
        Object[] R = new Object[nR];

        // Copy elements from the main array A into the left subarray L
        for (int i = 0; i < nL; i++)
            L[i] = A[lowerBound + i];

        // Copy elements from the main array A into the right subarray R
        for (int j = 0; j < nR; j++)
            R[j] = A[midPoint + 1 + j];

        // Initialize indices for L, R, and the main array A
        int i = 0, j = 0, k = lowerBound;

        // Merge the two subarrays into the main array A
        while (i < nL && j < nR) {
            // Compare elements of L and R and place the smaller one into A
            if ( ((T) L[i]).compareTo((T) R[j]) <= 0 ) {
                A[k] = (T) L[i];
                i++;
            } else {
                A[k] = (T) R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L (if any) into A
        while (i < nL) {
            A[k] = (T) L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R (if any) into A
        while (j < nR) {
            A[k] = (T) R[j];
            j++;
            k++;
        }
    }

    // Method to recursively sort the main array A using merge sort
    public void mergeSort(T[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int midPoint = (lowerBound + upperBound) / 2;
            mergeSort(A, lowerBound, midPoint); // Sort the left half
            mergeSort(A, midPoint + 1, upperBound); // Sort the right half
            merge(A, lowerBound, midPoint, upperBound); // Merge the sorted halves
        }
    }

    public static void main(String[] args) {
        // Example usage: sorting an array of strings
        String[] arr = {"banana", "apple", "orange", "grape", "pineapple"};
        AnyTypeMergeSort<String> sorter = new AnyTypeMergeSort<>();
        sorter.mergeSort(arr, 0, arr.length - 1);
        for (String item : arr) {
            System.out.println(item); // Print each item on a new line
        }
    }
}
