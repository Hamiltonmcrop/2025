/**************************************************************
* Class::  CSC-415-0A Spring 2024
* Name::   Professor Bierman
* Student ID:: 900000000
* GitHub-Name:: bierman
* Project:: Assignment 4 – Processing CSV Data with Threads
*
* File:: CSVTest.c
*
* Description:: Test csv parsing code
*
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLUMNCOUNT 4
#define ACTUALLINECOUNT 3
char * ActualHeader[] = {"Name - Last, First","Age","Favorite Color","Comments"};
char * ActualResult[ACTUALLINECOUNT][COLUMNCOUNT]={
                     {"Bierman, Robert","943","Blue","What can I say, this is a large comment"},
                     {"Smith, John","28","Green","I want to have a multiple\nline comment"},
                     {"Clark, Dwight \"The Catch\"","61","Red & Gold","1981 NFC Championship"}};

char ** csvopen (char * filename);
char ** csvnext (void);
char ** csvheader (void);
int csvclose (void);
char * defaultCSVFile = "CSVTestFile.csv";

// Free up the vector for each line
void releaseData (char * vector[], int count)
    {
    for (int i = 0; i < count; i++)
        {
        free(vector[i]);
        }
    free (vector);    
    }



int main (int argc, char ** argv)
    {
    char * file;
    int checkdata = 1;
    int maxprint = 100;
    
    file = defaultCSVFile;

    //Add code to process but not check any other CSV file
    if (argc >= 3)
        {
        file = argv[1];
        maxprint = atoi(argv[2]);
        checkdata = 0;
        }

    char ** header = csvopen (file);
    if (header == NULL)
        {
        printf ("Sorry csvopen returned NULL - exiting\n");
        return (-1);
        }

    int ColumnCount = 0;
    while ((header[ColumnCount] != NULL) && (ColumnCount < 50))
	++ColumnCount;

    if ((ColumnCount != COLUMNCOUNT) && checkdata)
        {
        printf ("The column count is %d but should be %d\n", ColumnCount, COLUMNCOUNT);
        return (-2);
        }

    // Print Header
    for (int i = 0;  i < ColumnCount; i++)
        {
        printf ("Header Column %02d: %s\n", i, header[i]);
        }

    //Loop through each record
    char **result;
    int lineCount = 0;
    while ((result = csvnext()) != NULL)
        {
        int ResultCount = 0;

        if ((lineCount >= ACTUALLINECOUNT)  && checkdata)
           {
           printf ("Error - Too Many Data Lines, should only be %d\n", ACTUALLINECOUNT);
           return (-5);
           }

        while ((result[ResultCount] != NULL) && (ResultCount < 50))
            ++ResultCount;

        // We should always have the same number of fields as the header
        if (ResultCount != ColumnCount)
           {
           printf ("Miss match of column count - Result Count: %d should be %d\n",
			ResultCount, ColumnCount);
           return (-3);
           }

        // Print and potentially check the data fields for this record
        if (maxprint > lineCount)
            {
            printf ("\nData for line %d\n", lineCount + 1);
            for (int i = 0;  i < ResultCount; i++)
                {
                printf ("Field %02d: %s\n", i, result[i]);

                if (checkdata)
                    {
                    if (strcmp (result[i], ActualResult[lineCount][i]) != 0)
                        {
                        printf ("Field Incorrect - Should be: %s\n", ActualResult[lineCount][i]);
                        return (-4);
                        }
                    }
                }
            }

        ++lineCount;

        releaseData (result, ResultCount);
        }

    int totalLines = csvclose();

    if ((totalLines != ACTUALLINECOUNT) && checkdata)
        {
        printf ("Total Lines returned from csvclose was %d should have been %d\n", 
                 totalLines, ACTUALLINECOUNT); 
        return (-6);
        }

    printf ("\n\nCSV Tests Passed\n");
    return 0;
    }

