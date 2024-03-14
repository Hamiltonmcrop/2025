/**
 * Class:  CSC-415-03 Spring 2023
 *Student ID
 *Project:Assignment 4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLUMNS 100
#define MAX_FIELD_LENGTH 1024

FILE *csv_file = NULL;
char *header[MAX_COLUMNS] = {NULL};

// Function to open a CSV file and read its header
char **csvopen(const char *filename) {
    csv_file = fopen(filename, "r");
    if (csv_file == NULL) {
        return NULL;  // Return NULL on failure
    }
    
    char line[MAX_FIELD_LENGTH];
    if (fgets(line, sizeof(line), csv_file) != NULL) {
        char *token = strtok(line, ",");
        int column = 0;
        while (token != NULL) {
            header[column] = strdup(token);
            token = strtok(NULL, ",");
            column++;
        }
        return header;
    } else {
        return NULL;  // Return NULL if unable to read header
    }
}

// Function to read the next line from the CSV file
char **csvread() {
    if (csv_file == NULL) {
        return NULL;
    }
    
    char line[MAX_FIELD_LENGTH];
    if (fgets(line, sizeof(line), csv_file) != NULL) {
        char *token = strtok(line, ",");
        char **fields = malloc(MAX_COLUMNS * sizeof(char *));
        int column = 0;
        while (token != NULL) {
            fields[column] = strdup(token);
            token = strtok(NULL, ",");
            column++;
        }
        fields[column] = NULL;  // Null-terminate the array
        return fields;
    } else {
        return NULL;  // Return NULL if unable to read a line
    }
}

// Function to get the header of the CSV file
char **getheader() {
    return header;
}

// Function to close the CSV file and free memory
int csvclose() {
    if (csv_file != NULL) {
        fclose(csv_file);
        csv_file = NULL;
        for (int i = 0; i < MAX_COLUMNS; i++) {
            free(header[i]);
            header[i] = NULL;
        }
        return 0;  // Return 0 on success
    } else {
        return -1;  // Return -1 if file is not open
    }
}

int main() {
    // Usage example:
    char **header = csvopen("CSVTestFile.csv");
    if (header != NULL) {
        printf("Header:\n");
        for (int i = 0; header[i] != NULL; i++) {
            printf("%s\n", header[i]);
        }
        
        char **row;
        while ((row = csvread()) != NULL) {
            printf("Row:\n");
            for (int i = 0; row[i] != NULL; i++) {
                printf("%s\n", row[i]);
                free(row[i]);  // Free memory allocated for each field
            }
            free(row);  // Free memory allocated for the row
        }
        
        csvclose();
    } else {
        printf("Failed to open CSV file.\n");
    }
    
    return 0;
}

