public class RearrangePositiveNegative {
    
    public static void rearrange(int[] arr) {
        int pivot = 0;

        // Move negative elements to the front
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] < 0) {
                int temp = arr[i];
                arr[i] = arr[pivot];
                arr[pivot] = temp;
                pivot++;
            }
        }
    }

    public static void main(String[] args) {
        int[] arr = {1, -1, 3, 2, -7, -5, 11, 6};

        rearrange(arr);

        System.out.print("Output: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
	System.out.print("\n");
    }
}

