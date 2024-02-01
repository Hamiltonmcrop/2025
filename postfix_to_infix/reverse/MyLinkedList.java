import java.util.Scanner;

class Node {
    String data;
    Node next;

    Node(String data) {
        this.data = data;
        this.next = null;
    }
}

public class MyLinkedList {
    private Node head;

    MyLinkedList() {
        head = null;
    }

    // Method to insert a new node at the end of the linked list
    void insert(String data) {
        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
        } else {
            Node current = head;
            while (current.next != null) {
                current = current.next;
            }
            current.next = newNode;
        }
    }

    // Method to print the linked list
    void print() {
        Node current = head;
        while (current != null) {
            System.out.print(current.data + " ");
            current = current.next;
        }
        System.out.println();
    }

    // Method to reverse the linked list
    void reverse() {
        Node prev = null;
        Node current = head;
        Node next;

        while (current != null) {
            next = current.next;
            current.next = prev;
            prev = current;
            current = next;
        }

        head = prev; // Update the new head after reversing
    }

    public static void main(String[] args) {
        MyLinkedList myList = new MyLinkedList();
        Scanner scanner = new Scanner(System.in);

        // Prompt user to enter values for the linked list
        System.out.println("Enter values for the linked list (enter 'done' to finish):");
        String value;
        while (true) {
            System.out.print("Enter a value (or 'done' to finish): ");
            value = scanner.nextLine();
            if (value.equals("done")) {
                break;
            }
            myList.insert(value);
        }

        // Print original linked list
        System.out.println("\nOriginal LinkedList:");
        myList.print();

        // Reverse linked list
        myList.reverse();

        // Print reversed linked list
        System.out.println("\nReversed LinkedList:");
        myList.print();

        scanner.close();
    }
}

