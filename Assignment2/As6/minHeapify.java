import java.util.Arrays;

/* 
 *  Building a MinHeapify java file.
 */
public class minHeapify {
    
    static void minHeapify(int arr[], int i, int size)
    {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        
        if (left < size && arr[left] < arr[smallest])
            smallest = left;
        
        if (right < size && arr[right] < arr[smallest])
            smallest = right;

        if (smallest != i)
        {
            int temp = arr[smallest];
            arr[smallest] = arr[i];
            arr[i] = temp;

            minHeapify(arr, smallest, size);
        }
    }
    
    static void buildMinHeap(int arr[], int n)
    {
        for (int i = (n-2)/2; i >= 0; i--)
            minHeapify(arr, i, n);
    }
    
    // Display Minheapify array.
    static void display(int arr[])
    {
        System.out.println(Arrays.toString(arr));
    }
    
    public static void main(String[] args) {

        int arr[] = {10, 15, 50, 4, 20};

        int n = arr.length;
        buildMinHeap(arr, n);
        
        display(arr);
    }
}

