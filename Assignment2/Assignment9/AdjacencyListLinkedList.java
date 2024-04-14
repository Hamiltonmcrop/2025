import java.util.Scanner;

public class AdjacencyListLinkedList {
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);

		/*
		 * Enter number of vertices
		 */
		System.out.print("Enter number of vertices:\n");
		int n = sc.nextInt();
		sc.nextLine();

		/*
		 * Enter list of vertices
		 */
		System.out.print("Enter list of vertices:\n");
		String input = sc.nextLine();
		String[] label = input.split(" ");

		/*
		 * Create and initialize the adjacency Matrix
		 */
		System.out.println("Enter 1 for Yes and 0 for No.");
		int[][] adjacencyMatrix = new int[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				System.out.print("Does " + label[i] + " have an edge with " + label[j] + "?\n");
				adjacencyMatrix[i][j] = sc.nextInt();
			}
		}
		sc.close();

		/*
		 * Print the adjacency Matrix
		 */
        System.out.println("\nFollowing graph is stored:");
		for(int i = 0; i < adjacencyMatrix.length; i++) {
			for(int j = 0; j < adjacencyMatrix[i].length; j++) {
				System.out.print(adjacencyMatrix[i][j] + " ");
			}
			System.out.println();
		}
	}
}

