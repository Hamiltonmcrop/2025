#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define error(m, c)                 \
    do                              \
    {                               \
        fprintf(stderr, "%s\n", m); \
        exit(c);                    \
    } while (0)
typedef enum
{
    NONE = 0,            // no flags are passed in CLAs
    CLEAR = 1,           //-c
    HEX = 1 << 1,        //-x
    SCIENTIFIC = 1 << 2, //-e
    TRUNCATED = 1 << 3,  //-s
} flags;
char *strip(char *input)
{
    char *rv = (char *)malloc(strlen(input) + 1);
    int left, right;
    for (left = 0, right = strlen(input) - 1;
         left < right && (input[left] == ' ' || input[right] == ' ');
         /*no update*/)
    {
        if (input[left] == ' ')
        {
            left++;
        }
        if (input[right] == ' ')
        {
            right--;
        }
    }
    strncpy(rv, input + left, right - left + 1);
    return rv;
}
int is_double(char *);
int is_int(char *);
int main(int argc, char *argv[])
{
    flags flag = NONE; // combination of flags
    char in_fmt[4] = "txt";
    char out_fmt[4] = "csv";
    int i = 1;
    while (argc != 1)
    {
        char *current_arg = argv[i++];
        if (current_arg[0] != '-')
            error("fatal error: illegal CLAs", 2);
        while (*++current_arg)
        {
            switch (*current_arg)
            {
            case 'i':
                if (strcmp(argv[i], "txt") && strcmp(argv[i], "csv"))
                    error("fatal error: illegal input format", 3);
                else if (!strcmp(argv[i], "txt"))
                    strcpy(in_fmt, "txt");
                else
                    strcpy(in_fmt, "csv");
                i++;
                argc--;
                break;
            case 'o':
                if (strcmp(argv[i], "txt") && strcmp(argv[i], "csv"))
                    error("fatal error: illegal output format", 4);
                else if (!strcmp(argv[i], "txt"))
                    strcpy(out_fmt, "txt");
                else
                    strcpy(out_fmt, "csv");
                i++;
                argc--;
                break;
            case 'c':
                flag |= CLEAR; // flag is an enum XXX0 | 0001 = XXX1
                break;
            case 'x':
                flag |= HEX;
                break;
            case 'e':
                flag |= SCIENTIFIC;
                break;
            case 's':
                flag |= TRUNCATED;
                break;
            default:
                error("fatal error: illegal option entered", 5);
            }
        }
        argc--;
    }

    fprintf(stderr, "Note: converting %s to %s with options: ", in_fmt, out_fmt);
    if (flag & CLEAR)
        fprintf(stderr, "-c ");
    if (flag & HEX) // HEX: 2 = 0010, flag: XX0X, HEX & flag = 0000
        fprintf(stderr, "-x ");
    if (flag & SCIENTIFIC)
        fprintf(stderr, "-e ");
    if (flag & TRUNCATED)
        fprintf(stderr, "-s ");
    fprintf(stderr, "\n");

    char line[1000];
    while (fgets(line, 1000, stdin))
    {
        char *line_ptr = line;
        line[strlen(line) - 1] = '\0';
        char *input_delimiter = strcmp(in_fmt, "csv") == 0 ? "," : "\t";
        char *ouput_delimiter = strcmp(in_fmt, "csv") == 0 ? "\t" : ",";
        char *cell;
        int ival;
        double dval;

        while (cell = strsep(&line_ptr, input_delimiter))
        {
            if (cell != line)
                printf("%s", ouput_delimiter);
            if (strlen(cell) == 0)
                continue;
            if (flag & CLEAR)
                cell = strip(cell);

            if (sscanf(cell, "%d", &ival) && is_int(cell))
            {
                if (flag & HEX)
                    printf("%x", ival);
                else
                    printf("%d", ival);
            }
            else if (sscanf(cell, "%lf", &dval) && is_double(cell))
            {
                if (flag & SCIENTIFIC)
                {
                    printf("%.3e", dval);
                }
                else
                    printf("%s", dval);
            }
            else
            {
                if (flag & TRUNCATED)
                    printf("%.5s", cell);
                else
                    printf("%s\n", cell);
            }
        }
        printf("\n");
    }
    return 0; // no error occured!
}

int is_int(char *input)
{
    // checks whether input can be a string representation of an int
    if (*input == '+' || *input == '-')
        input++;
    while (*input)
        if (!isdigit(*input++))
            return 0;
    return 1;
}

char *tolower_str(char *input)
{
    // lowers the case of characters in a string... it's called in is_double
    char *rv = strdup(input);
    int i = 0;
    while (*input)
        rv[i++] = tolower(*input++);
    return rv[i] = '\0', rv;
}

int is_double(char *input)
{
    // checks whether input can be a string representation of a double
    input = tolower_str(input);
    if (!strcmp(input, "inf") || !strcmp(input, "nan") ||
        !strcmp(input, "-inf"))
        return 1;
    if (strchr(input, 'e') != strrchr(input, 'e'))
        return 0;                       // at-most one 'e' is allowed!
    if (*input == '+' || *input == '-') // parse the sign
        input++;
    while (*input && *input != '.' && *input != 'e')
        if (!isdigit(*input++)) // parse the integer value
            return 0;
    if (*input++ == '.')
        while (*input && *input != 'e')
            if (!isdigit(*input++)) // parse the fraction
                return 0;
    if (*input++ == 'e')
    {
        if (*input == '+' || *input == '-')
            input++; // parse the sign of exponent
        while (*input)
            if (!isdigit(*input++)) // parse the exponent
                return 0;
    }
    return 1;
}
