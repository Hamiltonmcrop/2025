import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class AdjacencyMatrix {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        /*
	 * Create a linked list to store the vertices
	 */
        LinkedList<String> vertices = new LinkedList<>();

        /*
	 * Enter number of vertices
	 */
        System.out.print("Enter the number of vertices:\n");
        int n = sc.nextInt();
        sc.nextLine();

        /*
	 * Enter list of vertices
	 */
        System.out.println("Enter list of vertices:");
        String[] verticesInput = sc.nextLine().split(" ");

        /*
	 * Add vertices to the linked list
	 */
        for (String vertex : verticesInput) {
            vertices.add(vertex);
        }

        /*
	 * Create the adjacency list using a list of linked lists
	 */
        List<LinkedList<String>> adjacencyList = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adjacencyList.add(new LinkedList<>());
        }

        /*
	 * Storing the edges
	 */
        for (int i = 0; i < n; i++) {
            System.out.print("Enter adjacent vertices to " + vertices.get(i) + ":\n");
            String[] edgesInput = sc.nextLine().split(" ");
            for (String edge : edgesInput) {
                adjacencyList.get(i).add(edge);
            }
        }

        sc.close();

        System.out.println("\nFollowing graph is stored:");
        for (int i = 0; i < n; i++) {
            LinkedList<String> adjacentList = adjacencyList.get(i);
            for (int j = 0; j < adjacentList.size(); j++) {
                System.out.print(adjacentList.get(j) + " ");
            }
            System.out.println();
        }
    }
}

