import java.util.Arrays;

/* 
 *  building a Max Heap.
 */
public class BuildMaxHeap {
    
    static void MaxHeapify(int arr[],int i,int size)
    {
        int left=2*i+1;
        int right=2*i+2;
        int largest=i; // largest me i ka value dal diye hai.
        
        if(left<size && arr[left]>arr[largest])
            largest=left;
        
        if(right<size && arr[right]>arr[largest])
            largest=right;

        if(largest!=i)
        {
            //swap karange
            int temp=arr[largest];
            arr[largest]=arr[i];
            arr[i]=temp;

            MaxHeapify(arr, largest, size);
        }
    }
    static void Build_max_heap(int arr[],int n)
    {
        for(int i=(n-2)/2;i>=0;i--)
            MaxHeapify(arr, i,n);
    }
    // display Max heapify array.
    static void display(int arr[])
    {
        System.out.println(Arrays.toString(arr));
    }
    public static void main(String[] args) {

        int arr[]={10,15,50,4,20};

        int n=arr.length;
        Build_max_heap(arr, n);
        
        display(arr);
    }
}
