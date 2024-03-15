package com.company;

public class HashTable {
    Entry[] hashtable;
    private int size;
    private Entry deleted = new Entry(-1);

    public HashTable(int size) {
        this.size = size;
        hashtable = new Entry[size];
    }

    public int getSize() {
        return size;
    }

    public int linearProbing(int key, int attempt) {
        return (key + attempt) % size;
    }

    public int quadraticProbing(int key, int attempt) {
        return (key + attempt * attempt) % size;
    }

    public int doubleHashing(int key, int attempt) {
        int hash1 = key % size;
        int hash2 = 1 + (key % (size - 1));
        return (hash1 + attempt * hash2) % size;
    }

    public void insertLinearProbing(Entry a) {
        int key = a.key;
        int attempt = 0;
        while (attempt < size) {
            int index = linearProbing(key, attempt);
            if (hashtable[index] == null || hashtable[index] == deleted) {
                hashtable[index] = a;
                return;
            }
            attempt++;
        }
        System.out.println("hash table overflow");
    }

    public void insertQuadraticProbing(Entry a) {
        int key = a.key;
        int attempt = 0;
        while (attempt < size) {
            int index = quadraticProbing(key, attempt);
            if (hashtable[index] == null || hashtable[index] == deleted) {
                hashtable[index] = a;
                return;
            }
            attempt++;
        }
        System.out.println("hash table overflow");
    }

    public void insertDoubleHashing(Entry a) {
        int key = a.key;
        int attempt = 0;
        while (attempt < size) {
            int index = doubleHashing(key, attempt);
            if (hashtable[index] == null || hashtable[index] == deleted) {
                hashtable[index] = a;
                return;
            }
            attempt++;
        }
        System.out.println("hash table overflow");
    }

    public void delete(int key) {
        int attempt = 0;
        while (attempt < size) {
            int index = linearProbing(key, attempt); // You can choose any probing method here
            if (hashtable[index] == null) {
                System.out.println("nothing found to delete!");
                return;
            } else if (hashtable[index].key == key) {
                hashtable[index] = deleted;
                System.out.println("deleted");
                return;
            }
            attempt++;
        }
        System.out.println("nothing found to delete!");
    }

    public int search(int key) {
        int attempt = 0;
        while (attempt < size) {
            int index = linearProbing(key, attempt); // You can choose any probing method here
            if (hashtable[index] == null) {
                return -1;
            } else if (hashtable[index].key == key) {
                return index;
            }
            attempt++;
        }
        return -1;
    }
}

class Entry {
    protected int key;

    public Entry(int key) {
        this.key = key;
    }
}

