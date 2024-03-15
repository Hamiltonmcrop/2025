import java.util.Arrays;

/* 
 * Building a MinHeap.
 */
public class BuildMinHeap {
    
    static void MinHeapify(int arr[], int i, int size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        
        if (left < size && arr[left] < arr[smallest])
            smallest = left;
        
        if (right < size && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != i) {
            // swap karange
            int temp = arr[smallest];
            arr[smallest] = arr[i];
            arr[i] = temp;

            MinHeapify(arr, smallest, size);
        }
    }
    
    static void Build_min_heap(int arr[], int n) {
        for (int i = (n - 2) / 2; i >= 0; i--)
            MinHeapify(arr, i, n);
    }
    
    // Display BuildMinheap array.
    static void display(int arr[]) {
        System.out.println(Arrays.toString(arr));
    }
    
    public static void main(String[] args) {

        int arr[] = {10, 15, 50, 4, 20};

        int n = arr.length;
        Build_min_heap(arr, n);
        
        display(arr);
    }
}

