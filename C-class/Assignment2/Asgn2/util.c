#include "find.h"

// this function finds an occurrence of needle in haystack
// needle must be matched with a whole word in haystack...
static char* strstr_fully_matched(char* haystack, char* needle) {
  char* rv;
  char padded_needle[strlen(needle) + 3];
  padded_needle[0] = ' ';
  strcpy(padded_needle + 1, needle);
  padded_needle[strlen(needle) + 1] = ' ';
  padded_needle[strlen(needle) + 2] =
      '\0';  // pad the needle w/ spaces before and after
  if (!strcmp(needle, haystack))
    return haystack;  // needle matches the whole haystack
  if (!strncmp(haystack, padded_needle + 1, strlen(needle) + 1)) {
    return haystack;  // needle is at the beginning of haystack
  }
  if ((rv = strstr(haystack, padded_needle)) != NULL) {
    return rv + 1;  // needle is at the middle of haystack.
  }
  padded_needle[strlen(needle) + 1] = '\0';  // remove the last space
  if ((rv = strstr(haystack, padded_needle)) != NULL &&
      rv[strlen(padded_needle)] == '\0') {
    return rv + 1;  // needle is at the end of haystack.
  }
  return NULL;
}

// lowers the case of each character in its input string
static void to_lower(char* input) {
  for (int i = 0; i < strlen(input); i++) input[i] = tolower(input[i]);
}

// this function finds an occurrence of needle in haystack
// option specify case-sensitivity of search and whether needle should match a
// whole word
char* strstr_w_option(char* haystack, char* needle, flags option) {
  if (option & CASE) {
    to_lower(haystack = strdup(haystack));
    to_lower(needle = strdup(needle));
    if (option & MATCHED)
      return strstr_fully_matched(haystack, needle);
    else
      return strstr(haystack, needle);
  } else if (option & MATCHED)
    return strstr_fully_matched(haystack, needle);
  else
    return strstr(haystack, needle);
}

// subroutine used in qsort
static void swap(void** v, int i, int j) {
  void* temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

// quick sort on array of strings
void quicksort(char* str[], int left, int right) {
  int i, last;
  if (left >= right) return;
  swap(str, left, left + (right - left) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(str[i], str[left]) < 0) swap(str, ++last, i);
  swap(str, left, last);
  quicksort(str, left, last - 1);
  quicksort(str, last + 1, right);
}

char* truncate(char* initial, char* pattern, flags option) {
  if (strlen(initial) <= strlen(pattern) + 15) return initial;

  size_t len = strlen(initial);
  char* res = (char*)malloc(len + 1);

  char* found = strstr_w_option(initial, pattern, option);

  strncat(res, initial, 10);
  if (found - initial > strlen(res)) strncat(res, "...", 3);
  res = strncat(res, found, strlen(pattern));
  if (found + strlen(pattern) < initial + strlen(initial) - 6)
    strncat(res, "...", 3);
  strncat(res, initial + strlen(initial) - 5, 6);

  return res;
}