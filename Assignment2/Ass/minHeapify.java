import java.util.Arrays;

/* 
 *  Given a binary heap with one possible violation, fix the heap.
 */
public class minHeapify {
    public static void main(String[] args) {

        /* we have taken array because heap element is stored inside an array internally.*/
      
        int arr[] = { 40, 20, 30, 35, 25, 80, 32, 100, 70, 60 };
        int i = 0;  // index passed is 0
        minHeapify(arr, i);

        System.out.println(Arrays.toString(arr));
    }

    static void minHeapify(int arr[], int i) {
        
        int lt = left(i);     // to check left element 
        int rt = right(i);     // to check right element 
        int smallest = i;
        
        if (lt < arr.length && arr[lt] < arr[smallest])
            smallest = lt;

        if (rt < arr.length && arr[rt] < arr[smallest])
            smallest = rt;

        if (smallest != i) {
            int temp = arr[smallest];
            arr[smallest] = arr[i];
            arr[i] = temp;
            
            minHeapify(arr, smallest);
        }
    }
    
    static int left(int i) {
        return 2 * i + 1;
    }
    
    static int right(int i) {
        return 2 * i + 2;
    }
}

