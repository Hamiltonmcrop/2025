package saba_grid;

import java.util.Scanner;

public class saba_grid {

	// Checks if a string is empty or null.
	public static boolean is_empty(String s) {
		return s == null || s.length() == 0;
	}

	// Counts how many times the substring appears in the larger string.
	public static int count_matches(String text, String input) {
		if (is_empty(text) || is_empty(input)) {
			return 0;
		}
		return text.split(input, -1).length - 1;
	}

	// function to reverse the string for count check
	public static String reverse(String text) {
		String ret_string = "";
		for (int index = text.length() - 1; index >= 0; index--) {
			ret_string = ret_string + text.charAt(index);
		}
		return ret_string;
	}

	// check grid vertically from right to left
	public static int check_vertical(String[][] grid, int x, int y, String input) {
		int count = 0;
		for (int x1 = 0; x1 < x; x1++) {
			String row_string = "";
			for (int y1 = 0; y1 < y; y1++) {
				row_string += grid[y1][x1];
			}
			count = count + count_matches(row_string, input) + count_matches(reverse(row_string), input);
		}
		System.out.println("\nVertical Count: " + count);
		return count;
	}

	// check grid horizontally from right to left
	public static int check_horizontal(String[][] grid, int x, int y, String input) {
		int count = 0;
		for (int y1 = 0; y1 < y; y1++) {
			String row_string = "";
			for (int x1 = 0; x1 < x; x1++) {
				row_string += grid[y1][x1];
			}
			count = count + count_matches(row_string, input) + count_matches(reverse(row_string), input);
		}
		System.out.println("Horizontal Count: " + count);
		return count;
	}

	public static int check_diagonal1(String[][] grid, int x, int y, String input) {
		int count = 0;
		String row_string = "";

		// check grid diagonally from left to right
		for (int l_index = 0; l_index < Math.min(x, y); l_index++) {
			row_string = row_string + grid[l_index][l_index];
		}

		count = count + count_matches(row_string, input) + count_matches(reverse(row_string), input);
		System.out.println("Diagonal (left-to-right) Count: " + count);
		return count;
	}

	public static int check_diagonal2(String[][] grid, int x, int y, String input) {
		int count = 0;
		String row_string = "";

		// check grid diagonally from right to left
		for (int r_index = x - 1, c_index = 0; r_index >= 0 && c_index < y; r_index--, c_index++) {
			row_string = row_string + grid[r_index][c_index];
		}

		count = count + count_matches(row_string, input) + count_matches(reverse(row_string), input);
		System.out.println("Diagonal (right-to-left) Count: " + count);
		return count;
	}

	public static void main(String[] args) {
		int n; // Number of rows
		int m; // Number of columns

		Scanner input = new Scanner(System.in);
		// scanner inputs values of n >= 1
		do {
			System.out.print("Enter n value: ");
			n = input.nextInt();
			if (n < 1) {
				System.out.println("Invalid value: 'n' must be >= 1.");
			}
		} while (n < 1);
		// scanner inputs values of m <= 100
		do {
			System.out.print("Enter m value: ");
			m = input.nextInt();
			if (m > 100) {
				System.out.println("Invalid value: 'm' must be <= 100");
			}
		} while (m > 100);

		// scanner inputs in a 2D array of n x m
		String[][] grid = new String[n][m];
		System.out.print("Enter " + n + " lines of " + m + " characters: \n");
		input.nextLine();
		for (int i = 0; i < n; i++) {
			grid[i] = input.nextLine().split("");
			if (grid[i].length != m) {
				System.out.println("Invalid length.");
				i--;
			}
		}
		input.close();

		// Print the 2D array
		System.out.println("\nThis input will be stored in a 2D array of " + n + " x " + m + ": ");
		for (String[] row : grid) {
			for (String i : row) {
				System.out.print(i + " ");
			}
			System.out.println();
		}

		// methods and print word count
		String targetWord = "saba";
		int count = check_vertical(grid, n, m, targetWord);
		count += check_horizontal(grid, n, m, targetWord);
		count += check_diagonal1(grid, n, m, targetWord);
		count += check_diagonal2(grid, n, m, targetWord);
		System.out.println("\nThe word saba appears " + count + " times.");
	}
}
