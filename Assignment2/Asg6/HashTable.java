public class HashTable {
    private int[] table;
    private int size;

    public HashTable(int size) {
        this.size = size;
        table = new int[size];
        for (int i = 0; i < size; i++) {
            table[i] = -1; // Initialize all slots with -1 to represent empty slot
        }
    }

    // Linear probing index computation
    private int getLinearProbIndex(int key, int i) {
        return (getFirstHash(key) + i) % size;
    }

    // Quadratic probing index computation
    private int getQuadraticProbIndex(int key, int i) {
        return (getFirstHash(key) + i * i) % size;
    }

    // Double hashing index computation
    private int getDoubleHashIndex(int key, int i) {
        int h1 = getFirstHash(key);
        int h2 = getSecondHash(key);
        return (h1 + i * h2) % size;
    }

    // First hash function h1(k)
    private int getFirstHash(int key) {
        return key % size;
    }

    // Second hash function h2(k)
    private int getSecondHash(int key) {
        return 1 + (key % (size - 1));
    }

    // HASH-INSERT algorithm using linear probing
    public int hashInsertLinear(int key) {
        int i = 0;
        int j;
        do {
            j = getLinearProbIndex(key, i);
            if (table[j] == -1) {
                table[j] = key;
                return j;
            }
            i++;
        } while (i < size);
        System.out.println("Hash table overflow");
        return -1; // Overflow
    }

    // HASH-INSERT algorithm using quadratic probing
    public int hashInsertQuadratic(int key) {
        int i = 0;
        int j;
        do {
            j = getQuadraticProbIndex(key, i);
            if (table[j] == -1) {
                table[j] = key;
                return j;
            }
            i++;
        } while (i < size);
        System.out.println("Hash table overflow");
        return -1; // Overflow
    }

    // HASH-INSERT algorithm using double hashing
    public int hashInsertDouble(int key) {
        int i = 0;
        int j;
        do {
            j = getDoubleHashIndex(key, i);
            if (table[j] == -1) {
                table[j] = key;
                return j;
            }
            i++;
        } while (i < size);
        System.out.println("Hash table overflow");
        return -1; // Overflow or no empty slot found
    }

    public static void main(String[] args) {
        int size = 10; // Example size
        HashTable hashTable = new HashTable(size);

        // Example usage:
        hashTable.hashInsertLinear(5);
        hashTable.hashInsertLinear(15);
        hashTable.hashInsertLinear(25);
        hashTable.hashInsertLinear(35);

        hashTable.hashInsertQuadratic(6);
        hashTable.hashInsertQuadratic(16);
        hashTable.hashInsertQuadratic(26);
        hashTable.hashInsertQuadratic(36);

        hashTable.hashInsertDouble(7);
        hashTable.hashInsertDouble(17);
        hashTable.hashInsertDouble(27);
        hashTable.hashInsertDouble(37);
    }
}

