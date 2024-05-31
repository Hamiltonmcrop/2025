#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* lineptr[];
#define MAX_LINES 1000
#define MAX_LEN 1000

typedef enum {
  NUMBERED = 1,       // righttmost bit
  EXCEPT = 1 << 1,    // second rightmost bit
  SORTED = 1 << 2,    // third bit
  REVERSED = 1 << 3,  // fourth bit
  MATCHED = 1 << 4,   // fifth bit
  CASE = 1 << 5,      // sixth bit
  FIRST = 1 << 6,     // serventh bit
  PARTIAL = 1 << 7,   // eigth bit
} flags;

char* strstr_w_option(char* haystack, char* needle, flags option);
void quicksort(char* str[], int left, int right);
char* truncate(char* str, char* pattern, flags option);