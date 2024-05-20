#ifndef MAIN_H
#define MAIN_H

#define BUFFER_CAPACITY 1000

#include <stdbool.h>

/***
 * Strips the newline character from the end of the string, if present.
 */
void strip_newline(char *str);

/***
 * Determines if the string consists of only one unique character.
 */
bool is_univocal(char *str);

/***
 * Checks if the string characters form an arithmetic sequence in increasing order.
 */
bool is_consecutive_increasing(char *str);

/***
 * Checks if the string characters form an arithmetic sequence in decreasing order.
 */
bool is_consecutive_decreasing(char *str);

/***
 * Checks if the string is made up of three identical parts.
 */
bool is_tripartite_balanced(char *str);

/***
 * Checks if the string is made up of two identical halves.
 */
bool is_bipartite_balanced(char *str);

/***
 * Checks if the string reads the same forwards and backwards.
 */
bool is_mirror(char *str);

#endif

