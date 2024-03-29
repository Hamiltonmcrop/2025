import java.util.Random;

public class AnyTypeQuickSort<T extends Comparable<T>> {

    // Method to perform Randomized Quick Sort on an array of any type
    public void quickSort(T[] A, int lowerBound, int upperBound) {
        if (lowerBound < upperBound) {
            int q = randomizedPartition(A, lowerBound, upperBound);
            quickSort(A, lowerBound, q - 1); // Recursively sort the left subarray
            quickSort(A, q + 1, upperBound); // Recursively sort the right subarray
        }
    }

    // Method to perform Randomized Partition on an array of any type
    public int randomizedPartition(T[] A, int lowerBound, int upperBound) {
        Random rand = new Random();
        int i = rand.nextInt(upperBound - lowerBound + 1) + lowerBound; // Randomly select pivot index
        swap(A, i, upperBound); // Move the selected pivot to the end
        return partition(A, lowerBound, upperBound); // Perform partition
    }

    // Method to partition an array of any type
    public int partition(T[] A, int lowerBound, int upperBound) {
        T x = A[upperBound]; // Pivot element
        int i = lowerBound - 1; // Index of smaller element
        for (int j = lowerBound; j < upperBound; j++) {
            if (A[j].compareTo(x) <= 0) {
                i++;
                swap(A, i, j); // Swap if current element is smaller than or equal to pivot
            }
        }
        swap(A, i + 1, upperBound); // Swap pivot to its correct position
        return i + 1; // Return partitioning index
    }

    // Method to swap elements in an array of any type
    private void swap(T[] A, int i, int j) {
        T temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    public static void main(String[] args) {
        AnyTypeQuickSort<String> sorter = new AnyTypeQuickSort<>();
        String[] arr = {"banana", "apple", "orange", "grape", "pineapple"};
        sorter.quickSort(arr, 0, arr.length - 1);
        for (String item : arr) {
            System.out.println(item);
        }
    }
}
