public class main {
    public static void swap(int[] arr, int index1, int index2){
        int key;
        key = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = key;
    }
    public static int min(int a, int b){
        if(a>b) return b;
        else return a;
    }
    public static void minHeapify(int[] arr,int k, int n){
        int i = k;
        if(i*2+1<=n){
            int temp = min(arr[i*2],arr[i*2+1]);
            if(arr[i]>temp){
                if(temp == arr[i*2]){
                    swap(arr, i, i*2);
                    minHeapify(arr,i*2,n);
                }
                else {
                    swap (arr, i, i*2+1);
                    minHeapify(arr,i*2,n);
                }
            }
        }
    }
    public static void main(String[] args) throws Exception {
        int arr[] = {0, 4, 6, 2, 5, 3, 9, 7, 10, 1};
        int n = 9;
        int k = n;
        while(k>0){
            minHeapify(arr,k, n);
            k--;
        }
        
        for(int i = 1;i<=9;i++){
            System.out.print(arr[i]+" ");
        }
    }
}
