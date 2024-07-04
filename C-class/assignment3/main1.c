#include <stdio.h>
#include <string.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000

void print_numbers_from_csv(char *line)
{
    int number = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ',')
        {
            printf("%-25e\t", (double)number);
            number = 0;
        }
        else
        {
            number = number * 10 + (line[i] - '0');
        }
    }
    printf("\n");
}

int main()
{
    char csv_data[MAX_ROWS][MAX_COLS];
    printf("Enter CSV:\n");
    int row;
    for (row = 0; row < MAX_ROWS; row++)
    {
        if (fgets(csv_data[row], sizeof(csv_data[row]), stdin) == NULL)
            break;

        int length = strlen(csv_data[row]);
        if (length > 0 && csv_data[row][length - 1] == '\n')
            csv_data[row][length - 1] = '\0';

        if (strcmp(csv_data[row], "") == 0)
            break;
    }

    printf("Output TXT:\n");
    int num_rows = row;
    for (int j = 0; j < num_rows; j++)
    {
        print_numbers_from_csv(csv_data[j]);
    }

    return 0;
}
