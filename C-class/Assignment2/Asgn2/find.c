#include "find.h"

char* lineptr[MAX_LINES];

int readlines() {
  int len, nlines;
  char *p, line[MAX_LEN];
  nlines = 0;
  while (fgets(line, MAX_LEN, stdin)) {
    len = strlen(line);
    if (nlines >= MAX_LINES || (p = malloc(len + 1)) == NULL)
      return -1;
    else {
      if (line[len - 1] == '\n')  // dropping the newline at the end...
        line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

void error(int error_code) {
  printf("find: fatal error - Illegal usage. Error code: %d. Usage: \"%s\"\n",
         error_code, "find [-n] [-x] [-s] [-r] [-m] [-c] [-f] [-p] pattern");
  exit(error_code);
}

flags set_flags(int argc, char** argv) {
  flags option = 0;  // By default, all flags are down!
  for (int i = 1; i < argc - 1; i++) {
    if (argv[i][0] != '-')  // if argument doesn't start with -
      error(2);
    for (int j = 1; argv[i][j] != '\0'; j++) switch (argv[i][j]) {
        case 'n':
        case 'N':
          option |= NUMBERED;
          break;
        case 'x':
        case 'X':
          option |= EXCEPT;
          break;
        case 's':
        case 'S':
          option |= SORTED;
          break;
        case 'r':
        case 'R':
          option |= REVERSED;
          break;
        case 'm':
        case 'M':
          option |= MATCHED;
          break;
        case 'c':
        case 'C':
          option |= CASE;
          break;
        case 'f':
        case 'F':
          option |= FIRST;
          break;
        case 'p':
        case 'P':
          option |= PARTIAL;
          break;
        default:
          error(3);
      }
  }
  return option;
}

int main(int argc, char** argv) {
  if (argc < 2) error(1);
  char* pattern =
      strdup(argv[argc - 1]);  // the last CLA is considered to be the pattern
  flags option = set_flags(argc, argv);
  if ((option & REVERSED) && (option & SORTED))
    error(4);  // cannot print the output using both sorted and reversed
               // options...
  if ((option & EXCEPT) && (option & PARTIAL)) {
    printf(
        "fatal error: can't use -p and -x in the same execution\n");  // cannot
                                                                      // print
                                                                      // the
                                                                      // output
                                                                      // using
                                                                      // both
                                                                      // except
                                                                      // and
                                                                      // partial
                                                                      // options...
    exit(4);
  }

  int nlines = readlines();

  if (option & SORTED) quicksort(lineptr, 0, nlines - 1);

  if (option & REVERSED)
    for (int i = 0; i < nlines / 2; i++) {
      char* tmp = lineptr[i];
      lineptr[i] = lineptr[nlines - i - 1];
      lineptr[nlines - i - 1] = tmp;
    }

  char initial[10] = "";
  int printedLines = 0;
  for (int i = 0; i < nlines; i++) {  // first in first out
    char initial[10] = "\0";

    if (option & NUMBERED) {
      if (option & REVERSED) {
        sprintf(initial, "%d. ", nlines - i);
      } else {
        sprintf(initial, "%d. ", i + 1);
      }
    }

    // search for pattern in current line
    char* first_occurrence = strstr_w_option(lineptr[i], pattern, option);
    if ((option & FIRST) && (first_occurrence != NULL))
      sprintf(initial + strlen(initial),
              "@%d: ", strlen(lineptr[i]) - strlen(first_occurrence));

    // if except flag is up and pattern cannot be found in current line
    // or if except flag is down and pattern can be found in the current line
    if (((option & EXCEPT) != 0) != (first_occurrence != NULL)) {
      if (printedLines > 0) {
        printf("\n");
      }
      if (option & PARTIAL) {
        printf("%s%s", initial,
               truncate(lineptr[i], pattern,
                        option));  // print the line w/ number if numbered flag
                                   // is raised
      } else {
        printf(
            "%s%s", initial,
            lineptr[i]);  // print the line w/ number if numbered flag is raised
        // printf("%s%s\n", initial, lineptr[i]); // print the line w/ number if
        // numbered flag is raised
      }
      printedLines++;
    }
  }
  return 0;
}