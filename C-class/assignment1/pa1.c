#include "pa1.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/***
 * Removes the newline character from the end of the string, if it exists.
 */
void strip_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/***
 * Determines if the string consists of only one unique character.
 */
bool is_univocal(char *str) {
    for (int i = 1; str[i] != '\0'; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }
    return true;
}

/***
 * Checks if the string characters form an arithmetic sequence in increasing order.
 */
bool is_consecutive_increasing(char *str) {
    for (int i = 1; str[i] != '\0'; ++i) {
        if (str[i] - str[i - 1] != 1) {
            return false;
        }
    }
    return true;
}

/***
 * Checks if the string characters form an arithmetic sequence in decreasing order.
 */
bool is_consecutive_decreasing(char *str) {
    for (int i = 1; str[i] != '\0'; ++i) {
        if (str[i] - str[i - 1] != -1) {
            return false;
        }
    }
    return true;
}

/***
 * Checks if the string is made up of three identical parts.
 */
bool is_tripartite_balanced(char *str) {
    size_t len = strlen(str);
    if (len % 3 != 0) {
        return false;
    }
    size_t part_len = len / 3;
    for (size_t i = 0; i < part_len; ++i) {
        if (str[i] != str[i + part_len] || str[i] != str[i + 2 * part_len]) {
            return false;
        }
    }
    return true;
}

/***
 * Checks if the string is made up of two identical halves.
 */
bool is_bipartite_balanced(char *str) {
    size_t len = strlen(str);
    if (len % 2 != 0) {
        return false;
    }
    size_t part_len = len / 2;
    for (size_t i = 0; i < part_len; ++i) {
        if (str[i] != str[i + part_len]) {
            return false;
        }
    }
    return true;
}

/***
 * Checks if the string reads the same forwards and backwards.
 */
bool is_mirror(char *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    char input[BUFFER_CAPACITY];

    while (fgets(input, sizeof(input), stdin) != NULL) {
        strip_newline(input);

        if (is_univocal(input)) {
            printf("singleton\n");
        }
        if (is_consecutive_increasing(input)) {
            printf("arithmetic\n");
        }
        if (is_consecutive_decreasing(input)) {
            printf("reverse arithmetic\n");
        }
        if (is_tripartite_balanced(input)) {
            printf("balanced tripartite\n");
        }
        if (is_bipartite_balanced(input)) {
            printf("balanced bipartite\n");
        }
        if (is_mirror(input)) {
            printf("palindrome\n");
        }

        printf("\n");
    }

    return 0;
}

