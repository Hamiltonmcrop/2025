#include "find.h"

// This function finds an occurrence of needle in haystack
// Needle must be matched with a whole word in haystack...
static char* find_whole_word_match(char* text, char* word) { // strstr_fully_matched -> find_whole_word_match
  char* found_position;
  char padded_word[strlen(word) + 3];
  padded_word[0] = ' ';
  strcpy(padded_word + 1, word);
  padded_word[strlen(word) + 1] = ' ';
  padded_word[strlen(word) + 2] = '\0';  // Pad the word with spaces before and after

  if (!strcmp(word, text))
    return text;  // Word matches the whole text
  if (!strncmp(text, padded_word + 1, strlen(word) + 1)) {
    return text;  // Word is at the beginning of text
  }
  if ((found_position = strstr(text, padded_word)) != NULL) {
    return found_position + 1;  // Word is in the middle of text
  }
  padded_word[strlen(word) + 1] = '\0';  // Remove the last space
  if ((found_position = strstr(text, padded_word)) != NULL &&
      found_position[strlen(padded_word)] == '\0') {
    return found_position + 1;  // Word is at the end of text
  }
  return NULL;
}

// Lowers the case of each character in its input string
static void convert_to_lowercase(char* input) { // to_lower -> convert_to_lowercase
  for (int i = 0; i < strlen(input); i++) input[i] = tolower(input[i]);
}

// This function finds an occurrence of needle in haystack
// Options specify case-sensitivity of search and whether needle should match a whole word
char* strstr_w_option(char* text, char* word, flags options) {
  if (options & CASE) {
    char* lower_text = strdup(text);
    char* lower_word = strdup(word);
    convert_to_lowercase(lower_text);
    convert_to_lowercase(lower_word);
    if (options & MATCHED) {
      char* result = find_whole_word_match(lower_text, lower_word);
      free(lower_text);
      free(lower_word);
      return result;
    } else {
      char* result = strstr(lower_text, lower_word);
      free(lower_text);
      free(lower_word);
      return result;
    }
  } else if (options & MATCHED) {
    return find_whole_word_match(text, word);
  } else {
    return strstr(text, word);
  }
}

// Subroutine used in qsort
static void swap_elements(void** array, int i, int j) { // swap -> swap_elements
  void* temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

// Quick sort on array of strings
void quicksort(char* strings[], int left, int right) {
  int i, last;
  if (left >= right) return;
  swap_elements(strings, left, left + (right - left) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(strings[i], strings[left]) < 0) swap_elements(strings, ++last, i);
  swap_elements(strings, left, last);
  quicksort(strings, left, last - 1);
  quicksort(strings, last + 1, right);
}

char* truncate(char* text, char* word, flags options) {
  if (strlen(text) <= strlen(word) + 15) return text;

  size_t text_length = strlen(text);
  char* result = (char*)malloc(text_length + 1);
  result[0] = '\0';  // Initialize the result string

  char* match_position = strstr_w_option(text, word, options);

  strncat(result, text, 10);
  if (match_position - text > strlen(result)) strncat(result, "...", 3);
  result = strncat(result, match_position, strlen(word));
  if (match_position + strlen(word) < text + text_length - 6)
    strncat(result, "...", 3);
  strncat(result, text + text_length - 5, 6);

  return result;
}

