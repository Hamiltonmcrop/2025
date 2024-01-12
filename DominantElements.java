import java.util.ArrayList;
import java.util.List;

public class DominantElements {

    public static List<Integer> findDominantElements(int[] arr) {
        List<Integer> result = new ArrayList<>();
        
        if (arr.length == 0) {
            return result;
        }
        
        int maxRight = arr[arr.length - 1]; // Rightmost element is always dominant
        result.add(maxRight);
        
        for (int i = arr.length - 2; i >= 0; i--) {
            if (arr[i] > maxRight) {
                maxRight = arr[i];
                result.add(maxRight);
            }
        }
        
        return result;
    }

    public static void main(String[] args) {
        int[] array = {16, 17, 4, 3, 5, 2};
        List<Integer> dominants = findDominantElements(array);
        System.out.println("Dominant elements are: " + dominants);
    }
}

