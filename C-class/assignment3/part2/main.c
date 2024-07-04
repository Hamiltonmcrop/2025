#include "hash.h"

/**
 * Determines if a string can be rearranged to form a palindrome using a hashmap.
 */
int is_palindrome_candidate_hashmap(char *str) {
    // Hashmap contains frequencies
    hashmap hm = hash_init();
    char *keys[100];
    size_t size = 0;

    // Populate hashmap by character frequencies
    for (int i = 0; i < strlen(str); i++) {
        char *key = malloc(2 * sizeof(char));
        key[0] = str[i];
        key[1] = '\0';
        if (!contains_key(hm, key)) {
            keys[size] = key;
            size += 1;
            put(&hm, key, 0);
        }
        int value = get(hm, key);
        put(&hm, key, value + 1);
    }

    // Count odd frequencies
    int odd_count = 0;
    for (int i = 0; i < size; i++) {
        int value = get(hm, keys[i]);
        // Even
        if (value % 2 == 0)
            continue;
        // Odd
        odd_count += 1;
    }

    // Free
    for (int i = 0; i < size; i++)
        free(keys[i]);

    return odd_count < 2;
}

/**
 * Determines if a string can be rearranged to form a palindrome using a hashset.
 */
int is_palindrome_candidate_hashset(char *str) {
    // Hashset contains odds
    hashset hs = set_init();
    size_t size = 0;

    char key[2] = {0};
    for (int i = 0; i < strlen(str); i++) {
        key[0] = str[i];
        if (!search(hs, key)) {
            insert(&hs, key);
            size += 1;
        } else {
            remove_key(&hs, key);
            size -= 1;
        }
    }

    return size < 2;
}

/**
 * Main function to test palindrome candidates.
 */
int main() {
    char *str = "helloworld!";
    printf("%s: %d (hashmap)\n", str, is_palindrome_candidate_hashmap(str));
    printf("%s: %d (hashset)\n", str, is_palindrome_candidate_hashset(str));
    str = "mississippi";
    printf("%s: %d (hashmap)\n", str, is_palindrome_candidate_hashmap(str));
    printf("%s: %d (hashset)\n", str, is_palindrome_candidate_hashset(str));
    return 0;
}

