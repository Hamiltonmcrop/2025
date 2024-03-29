import java.util.Random;

public class IntegerQuickSort {

    // Method to perform Randomized Quick Sort on an integer array
    public void quickSort(int[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int q = randomizedPartition(A, lowerBound, upperBound);
            quickSort(A, lowerBound, q - 1); // Recursively sort the left subarray
            quickSort(A, q + 1, upperBound); // Recursively sort the right subarray
        }
    }

    // Method to perform Randomized Partition on an integer array
    public int randomizedPartition(int[] A, int lowerBound, int upperBound) {
        Random rand = new Random();
        int i = rand.nextInt(upperBound - lowerBound + 1) + lowerBound; // Randomly select pivot index
        swap(A, i, upperBound); // Move the selected pivot to the end
        return partition(A, lowerBound, upperBound); // Perform partition
    }

    // Method to partition an integer array
    public int partition(int[] A, int lowerBound, int upperBound) {
        int x = A[upperBound]; // Pivot element
        int i = lowerBound - 1; // Index of smaller element
        for (int j = lowerBound; j < upperBound; j++) {
            if (A[j] <= x) {
                i++;
                swap(A, i, j); // Swap if current element is smaller than or equal to pivot
            }
        }
        swap(A, i + 1, upperBound); // Swap pivot to its correct position
        return i + 1; // Return partitioning index
    }

    // Method to swap elements in an integer array
    private void swap(int[] A, int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    public static void main(String[] args) {
        IntegerQuickSort sorter = new IntegerQuickSort();
        int[] arr = {12, 11, 13, 5, 6, 7};
        sorter.quickSort(arr, 0, arr.length - 1);
        for (int num : arr) {
            System.out.println(num);
        }
    }
}
