public class IntegerMergeSort {

    // Method to recursively sort the array A using merge sort
    public void mergeSort(int[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int midPoint = (lowerBound + upperBound) / 2; // Calculate the midpoint
            mergeSort(A, lowerBound, midPoint); // Recursively sort the left half
            mergeSort(A, midPoint + 1, upperBound); // Recursively sort the right half
            merge(A, lowerBound, midPoint, upperBound); // Merge the sorted halves
        }
    }

    // Method to merge two sorted subarrays into one sorted array
    public void merge(int[] A, int lowerBound, int midPoint, int upperBound) {
        int nL = midPoint - lowerBound + 1; // Length of A[p:q]
        int nR = upperBound - midPoint; // Length of (A,q+1,r)
        int[] L = new int[nL];
        int[] R = new int[nR];

        // Copy elements from the main array A into the left subarray L
        for (int i = 0; i < nL; i++) {
            L[i] = A[lowerBound + i];
        }

        // Copy elements from the main array A into the right subarray R
        for (int j = 0; j < nR; j++) {
            R[j] = A[midPoint + 1 + j];
        }

        int i = 0; // i indexes the smallest remaining element in L
        int j = 0; // j indexes the smallest remaining element in R
        int k = lowerBound; // k indexes the location in A to fill

        // Merge the two subarrays into the main array A
        while (i < nL && j < nR) {
            if (L[i] <= R[j]) {
                A[k] = L[i];
                i++;
            } else {
                A[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L (if any) into A
        while (i < nL) {
            A[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R (if any) into A
        while (j < nR) {
            A[k] = R[j];
            j++;
            k++;
        }
    }

    public static void main(String[] args) {
        IntegerMergeSort sorter = new IntegerMergeSort();
        int[] arr = {12, 11, 13, 5, 6, 7};
        sorter.mergeSort(arr, 0, arr.length - 1);
        for (int num : arr) {
            System.out.println(num); // Print each item on a new line
        }
    }
}
