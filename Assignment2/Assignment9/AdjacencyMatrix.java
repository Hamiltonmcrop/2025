import java.util.Scanner;

public class AdjacencyMatrix {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);

		/*
		 * Enter number of vertices
		 */
		System.out.print("Enter number of vertices:\n");
		int n = sc.nextInt();
		sc.nextLine();

		/*
		 * Create the vertex labels
		 */
		System.out.print("Enter list of vertices:\n");
		String input = sc.nextLine();
		String[] label = input.split(" ");

		/*
		 * Create the ragged array to store the adjacency list
		 */
		int[][] adjacencyList = new int[n][];
		for (int i = 0; i < n; i++) {
			System.out.print("How many edges are associated with " + label[i] + "?\n");
			int numEdges = sc.nextInt();
			sc.nextLine();

			/*
			 * Create an array to store the adjacent vertices
			 */
			adjacencyList[i] = new int[numEdges];

			System.out.print("Enter adjacent vertices to " + label[i] + "\n");
			String adjacentVerticesInput = sc.nextLine();
			String[] adjacentVertices = adjacentVerticesInput.split(" ");
			for (int j = 0; j < numEdges; j++) {
				for (int k = 0; k < n; k++) {
					if (label[k].equals(adjacentVertices[j])) {
						adjacencyList[i][j] = k;
						break;
					}
				}
			}
		}

		sc.close();

		/*
		 * Print the ragged ragged adjacency list
		 */
		System.out.println("\nFollowing graph is stored:");
		for (int i = 0; i < adjacencyList.length; i++) {
			for (int j = 0; j < adjacencyList[i].length; j++) {
				System.out.print(adjacencyList[i][j] + " ");
			}
			System.out.println();
		}
	}
}


