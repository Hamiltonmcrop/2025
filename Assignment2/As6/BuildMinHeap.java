import java.util.Arrays;

/* 
 *  creating min heap with given random array.
 */
public class BuildMinHeap {
    
    static void buildMInHeap(int arr[],int size)
    {
        for(int i=(size-2)/2;i>=0;i--)
        {
            heapify(arr,i);   //calling heapify function for each node from last node heap parent
        }
    }
    // heapify function.
    static void heapify(int[] arr,int i)
    {
        int le=2*i+1;
        int re=2*i+2;
        int smallest=i;

        if(le<arr.length && arr[le]<arr[i])
            smallest=le;
        
        if(re<arr.length && arr[re]<arr[smallest])
            smallest=re;
        
        if(smallest!=i)
        {
            //swap kiye hai.
            int temp=arr[smallest];
            arr[smallest]=arr[i];
            arr[i]=temp;

            heapify(arr, smallest);
        }
    }
    //function to display modified heap or new min heap.
    static void display(int arr[])
    {
        System.out.println(Arrays.toString(arr));
    }
    public static void main(String[] args) {
        
        int arr[]={10,5,20,2,4,8};
        int size=arr.length;
        
        buildMInHeap(arr,size);
        display(arr);
    }
}
