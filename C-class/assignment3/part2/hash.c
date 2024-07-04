#include "hash.h"

/**
 * Helper function to create a new map node.
 */
map_node *new_map_node(char *key, int value) {
    map_node *node = (map_node *)malloc(sizeof(map_node));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

/**
 * Helper function to create a new set node.
 */
node *new_node(char *value) {
    node *n = (node *)malloc(sizeof(node));
    n->value = strdup(value);
    n->next = NULL;
    return n;
}

/**
 * Initializes a new hashmap.
 */
hashmap hash_init(void) {
    hashmap hm;
    hm.table = (map_node **)calloc(BINS, sizeof(map_node *));
    hm.size = 0;
    hm.bins = BINS;
    return hm;
}

/**
 * Computes the hash for a given key.
 */
unsigned int hash(char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // Convert our string to an integer
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    // Make sure value is 0 <= value < TABLE_SIZE
    value = value % BINS;

    return value;
}

/**
 * Checks if the hashmap contains the given key.
 */
int contains_key(hashmap hm, char *key) {
    unsigned int bin = hash(key);
    map_node *node = hm.table[bin];

    while (node != NULL && strcmp(key, node->key) != 0) {
        node = node->next;
    }

    return node != NULL;
}

/**
 * Retrieves the value for a given key in the hashmap.
 */
int get(hashmap hm, char *key) {
    unsigned int bin = hash(key);
    map_node *node = hm.table[bin];

    while (node != NULL && strcmp(key, node->key) != 0) {
        node = node->next;
    }

    if (node == NULL) return -1; // Not found
    return node->value;
}

/**
 * Puts a key-value pair into the hashmap.
 */
int put(hashmap *hm, char *key, int value) {
    unsigned int bin = hash(key);
    map_node *node = hm->table[bin];

    // Check if the key already exists in the map
    while (node != NULL && strcmp(key, node->key) != 0) {
        node = node->next;
    }

    if (node != NULL) {
        node->value = value;
    } else {
        node = new_map_node(key, value);
        node->next = hm->table[bin];
        hm->table[bin] = node;
        hm->size++;
    }

    return value;
}

/**
 * Initializes a new hashset.
 */
hashset set_init(void) {
    hashset hs;
    hs.table = (node **)calloc(BINS, sizeof(node *));
    hs.size = 0;
    hs.bins = BINS;
    return hs;
}

/**
 * Checks if the hashset contains the given key.
 */
int search(hashset hs, char *key) {
    unsigned int bin = hash(key);
    node *n = hs.table[bin];

    while (n != NULL && strcmp(key, n->value) != 0) {
        n = n->next;
    }

    return n != NULL;
}

/**
 * Inserts a key into the hashset.
 */
int insert(hashset *hs, char *key) {
    unsigned int bin = hash(key);
    node *n = hs->table[bin];

    if (n == NULL) {
        hs->table[bin] = new_node(key);
    } else {
        while (n->next != NULL && strcmp(key, n->value) != 0) {
            n = n->next;
        }
        if (strcmp(key, n->value) != 0) {
            n->next = new_node(key);
        }
    }
    hs->size++;
    return 1;
}

/**
 * Removes a key from the hashset.
 */
void remove_key(hashset *hs, char *key) {
    unsigned int bin = hash(key);
    node *n = hs->table[bin];
    node *prev = NULL;

    while (n != NULL && strcmp(key, n->value) != 0) {
        prev = n;
        n = n->next;
    }

    if (n == NULL) return;

    if (prev == NULL) {
        hs->table[bin] = n->next;
    } else {
        prev->next = n->next;
    }

    free(n->value);
    free(n);
    hs->size--;
}

