import java.util.Scanner;

public class SabaGrid {

    public static boolean isEmpty(String s) {
        return s == null || s.length() == 0;
    }

    public static int countMatches(String text, String input) {
        if (isEmpty(text) || isEmpty(input)) {
            return 0;
        }
        return text.split(input, -1).length - 1;
    }

    public static String reverse(String text) {
        StringBuilder retString = new StringBuilder();
        for (int index = text.length() - 1; index >= 0; index--) {
            retString.append(text.charAt(index));
        }
        return retString.toString();
    }

    public static int checkVertical(String[][] grid, int x, int y, String input) {
        int count = 0;
        for (int x1 = 0; x1 < x; x1++) {
            StringBuilder rowString = new StringBuilder();
            for (int y1 = 0; y1 < y; y1++) {
                rowString.append(grid[x1][y1]);
            }
            count += countMatches(rowString.toString(), input) + countMatches(reverse(rowString.toString()), input);
        }
        return count;
    }

    public static int checkHorizontal(String[][] grid, int x, int y, String input) {
        int count = 0;
        for (int y1 = 0; y1 < y; y1++) {
            StringBuilder rowString = new StringBuilder();
            for (int x1 = 0; x1 < x; x1++) {
                rowString.append(grid[x1][y1]);
            }
            count += countMatches(rowString.toString(), input) + countMatches(reverse(rowString.toString()), input);
        }
        return count;
    }

    public static int checkDiagonal1(String[][] grid, int x, int y, String input) {
        int count = 0;
        StringBuilder rowString = new StringBuilder();

        for (int lIndex = 0; lIndex < Math.min(x, y); lIndex++) {
            rowString.append(grid[lIndex][lIndex]);
        }

        count += countMatches(rowString.toString(), input) + countMatches(reverse(rowString.toString()), input);
        return count;
    }

    public static int checkDiagonal2(String[][] grid, int x, int y, String input) {
        int count = 0;
        StringBuilder rowString = new StringBuilder();

        for (int rIndex = x - 1, cIndex = 0; rIndex >= 0 && cIndex < y; rIndex--, cIndex++) {
            rowString.append(grid[rIndex][cIndex]);
        }

        count += countMatches(rowString.toString(), input) + countMatches(reverse(rowString.toString()), input);
        return count;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n, m; // Number of rows and columns

        do {
            System.out.print("Enter n value: ");
            n = input.nextInt();
            if (n < 1) {
                System.out.println("Invalid value: 'n' must be >= 1.");
            }
        } while (n < 1);

        do {
            System.out.print("Enter m value: ");
            m = input.nextInt();
            if (m > 100) {
                System.out.println("Invalid value: 'm' must be <= 100");
            }
        } while (m > 100);

        String[][] grid = new String[n][m];

        System.out.println("Enter " + n + " lines of " + m + " characters:");
        input.nextLine(); // consume the newline
        for (int i = 0; i < n; i++) {
            grid[i] = input.nextLine().split("");
            if (grid[i].length != m) {
                System.out.println("Invalid length.");
                i--;
            }
        }
        input.close();

        System.out.println("\nThis input will be stored in a 2D array of " + n + " x " + m + ": ");
        for (String[] row : grid) {
            for (String i : row) {
                System.out.print(i + " ");
            }
            System.out.println();
        }

        String targetWord = "saba";
        int count = checkVertical(grid, n, m, targetWord);
        count += checkHorizontal(grid, n, m, targetWord);
        count += checkDiagonal1(grid, n, m, targetWord);
        count += checkDiagonal2(grid, n, m, targetWord);

        System.out.println("\nThe word saba appears " + count + " times.");
    }
}

