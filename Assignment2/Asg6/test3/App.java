package com.company;

public class App {

    public static void main(String[] args) {

        HashTable hashTable = new HashTable(11);

        // Insert using linear probing
        hashTable.insertLinearProbing(new Entry(19));
        hashTable.insertLinearProbing(new Entry(24));
        hashTable.insertLinearProbing(new Entry(46));
        hashTable.insertLinearProbing(new Entry(64));
        hashTable.insertLinearProbing(new Entry(98));
        hashTable.insertLinearProbing(new Entry(77));
        hashTable.insertLinearProbing(new Entry(51));

        System.out.println("Linear Probing:");
        hashTable.printHashTable();

        // Delete using linear probing
        hashTable.delete(19);
        hashTable.delete(46);
        hashTable.delete(12);

        System.out.println("After Deletions:");
        hashTable.printHashTable();

        // Insert using quadratic probing
        hashTable.insertQuadraticProbing(new Entry(45));
        hashTable.insertQuadraticProbing(new Entry(54));
        hashTable.insertQuadraticProbing(new Entry(61));
        hashTable.insertQuadraticProbing(new Entry(77));

        System.out.println("Quadratic Probing:");
        hashTable.printHashTable();

        // Search
        System.out.println("Search:");
        System.out.println(hashTable.search(75));
        System.out.println(hashTable.search(51));
    }
}

