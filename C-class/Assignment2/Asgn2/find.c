#include "find.h"

char* line_storage[MAX_LINES]; // lineptr -> line_storage

int read_input_lines() { // readlines -> read_input_lines
  int line_length, total_lines;
  char *line_pointer, current_line[MAX_LEN]; // p -> line_pointer, line -> current_line
  total_lines = 0; // nlines -> total_lines
  while (fgets(current_line, MAX_LEN, stdin)) {
    line_length = strlen(current_line);
    if (total_lines >= MAX_LINES || (line_pointer = malloc(line_length + 1)) == NULL)
      return -1;
    else {
      if (current_line[line_length - 1] == '\n')  // dropping the newline at the end...
        current_line[line_length - 1] = '\0';
      strcpy(line_pointer, current_line);
      line_storage[total_lines++] = line_pointer;
    }
  }
  return total_lines;
}

void show_error(int error_code) { // error -> show_error
  printf("find: fatal error - Illegal usage. Error code: %d. Usage: \"%s\"\n",
         error_code, "find [-n] [-x] [-s] [-r] [-m] [-c] [-f] [-p] pattern");
  exit(error_code);
}

flags configure_flags(int arg_count, char** arg_values) { // set_flags -> configure_flags, argc -> arg_count, argv -> arg_values
  flags options = 0;  // By default, all flags are down!
  for (int i = 1; i < arg_count - 1; i++) {
    if (arg_values[i][0] != '-')  // if argument doesn't start with -
      show_error(2);
    for (int j = 1; arg_values[i][j] != '\0'; j++) switch (arg_values[i][j]) {
        case 'n':
        case 'N':
          options |= NUMBERED;
          break;
        case 'x':
        case 'X':
          options |= EXCEPT;
          break;
        case 's':
        case 'S':
          options |= SORTED;
          break;
        case 'r':
        case 'R':
          options |= REVERSED;
          break;
        case 'm':
        case 'M':
          options |= MATCHED;
          break;
        case 'c':
        case 'C':
          options |= CASE;
          break;
        case 'f':
        case 'F':
          options |= FIRST;
          break;
        case 'p':
        case 'P':
          options |= PARTIAL;
          break;
        default:
          show_error(3);
      }
  }
  return options;
}

int main(int arg_count, char** arg_values) { // argc -> arg_count, argv -> arg_values
  if (arg_count < 2) show_error(1);
  char* search_pattern = strdup(arg_values[arg_count - 1]);  // pattern -> search_pattern, argv -> arg_values, argc -> arg_count
  flags options = configure_flags(arg_count, arg_values);
  if ((options & REVERSED) && (options & SORTED))
    show_error(4);  // cannot print the output using both sorted and reversed options...
  if ((options & EXCEPT) && (options & PARTIAL)) {
    printf("fatal error: can't use -p and -x in the same execution\n");
    exit(4);
  }

  int total_lines = read_input_lines();

  if (options & SORTED) quicksort(line_storage, 0, total_lines - 1);

  if (options & REVERSED)
    for (int i = 0; i < total_lines / 2; i++) {
      char* temp_line = line_storage[i];
      line_storage[i] = line_storage[total_lines - i - 1];
      line_storage[total_lines - i - 1] = temp_line;
    }

  char prefix[10] = "";
  int lines_printed = 0; // printedLines -> lines_printed
  for (int i = 0; i < total_lines; i++) {
    char prefix[10] = "\0";

    if (options & NUMBERED) {
      if (options & REVERSED) {
        sprintf(prefix, "%d. ", total_lines - i);
      } else {
        sprintf(prefix, "%d. ", i + 1);
      }
    }

    char* first_match = strstr_w_option(line_storage[i], search_pattern, options);
    if ((options & FIRST) && (first_match != NULL))
      sprintf(prefix + strlen(prefix),
              "@%d: ", strlen(line_storage[i]) - strlen(first_match));

    if (((options & EXCEPT) != 0) != (first_match != NULL)) {
      if (lines_printed > 0) {
        printf("\n");
      }
      if (options & PARTIAL) {
        printf("%s%s", prefix,
               truncate(line_storage[i], search_pattern, options));
      } else {
        printf("%s%s", prefix, line_storage[i]);
      }
      lines_printed++;
    }
  }
  return 0;
}

