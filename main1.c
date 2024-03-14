/**************************************************************
* Class:  CSC-415-03 Spring 2023
* Name: Mahdi Hassanpour
* Student ID: 922278744 
* GitHub ID: MHP200
* Project: Assignment 4 – Word Blast
*
* File: <name of this file>
*
* Description:
* For this assignment, your program is to read War and Peace (a text copy is included with this assignment)
* and it is to count and tally each of the words that are 6 or more characters long.  And again, you will only
* use Linux (not library) file functions, i.e. open, close, read, lseek, pread.
***************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

// You may find this Useful
char * delim = "\"\'.“”‘’?:;-,—*($%)! \t\n\x0A\r";

// defining global variables
#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif
// Defining minimum characters to be 6
#define MINIMUMCHARS 6
// Defining number of words we need to display
#define TOP 10
#define WL_SIZE 2500

// defining structures

pthread_mutex_t lock;

// Defining infoOfChunk structure which will have start and size index as long datatype so that it'll not give out of bound error
typedef struct infoOfChunk
{
    char *filename;
    int id;
    long start;
    long size;
} infoOfChunk, *infoOfChunk_p;
// Defining wordsEntryF structure which will have 2 data members, word which will be a string and count, which is a counter variable
typedef struct wordsEntryF
{
    char *word;
    int count;
} wordsEntryF, *wordsEntryF_p;

volatile wordsEntryF_p wList = NULL;
volatile int counter2 = 0;
int maxSize = 0;

// Defining functions
//  This will add a new word
void addNewWord(char *word)
{
    // for loop
    for (int i = 0; i < counter2; i++)
    {
        // conditionals to compare the two strings
        if (strcasecmp(wList[i].word, word) == 0)
        {
            pthread_mutex_lock(&lock);
            wList[i].count = wList[i].count + 1;
            pthread_mutex_unlock(&lock);
            return;
        }
    }
    pthread_mutex_lock(&lock);
    // conditionals
    if (counter2 >= maxSize)
    {
        maxSize = maxSize + WL_SIZE;
        // conditionals
        if (wList == NULL)
        {
            // assigning storage to wList variable using malloc function
            wList = malloc(sizeof(wordsEntryF) * maxSize);
            // conditionals if wList returns null pointer
            if (wList == NULL)
            {
                printf("ERROR: Initial malloc of wList failed - trying to allocate %lu bytes\n", sizeof(wordsEntryF) * maxSize);
                exit(-2);
            }
        }
        else
        {
            wordsEntryF_p reallocRet = realloc(wList, sizeof(wordsEntryF) * maxSize);
            // conditionals
            if (reallocRet == NULL)
            {
                printf("ERROR: Realloc of wList failed - trying to allocate %lu bytes\n", sizeof(wordsEntryF) * maxSize);
                exit(-2);
            }
            wList = reallocRet;
        }
    }
    wList[counter2].word = malloc(strlen(word) + 2);
    strcpy(wList[counter2].word, word);
    wList[counter2].count = 1;
    counter2++; // Incrementing the counter
    pthread_mutex_unlock(&lock);
}

// Processing the Chunk Function
void *processChunk(void *p)
{
    infoOfChunk_p info = (infoOfChunk_p)p;
    char *buf;
    char *word;
    char *saveptr;
    int fDesc;

    buf = malloc(info->size + 4);
    // conditionals if buffer returns null value
    if (buf == NULL)
    {
        return NULL;
    }

    fDesc = open(info->filename, O_RDONLY);
    // conditionals
    if (fDesc == 0)
    {
        free(buf);
        return NULL;
    }

    lseek(fDesc, info->start, SEEK_SET);
    long res = read(fDesc, buf, info->size);
    close(fDesc);
    buf[info->size] = 0;
    buf[info->size + 1] = 0;
    word = strtok_r(buf, delim, &saveptr);
    // while loop
    while (word != NULL)
    {
        // conditionals
        if (strlen(word) >= MINIMUMCHARS)
        {
            addNewWord(word);
        }
        word = strtok_r(NULL, delim, &saveptr);
    }
    // deleting the dynamic pointer to save the space
    free(buf);
    return NULL;
}

// Main Function
// Main Function
int main(int argc, char *argv[])
{
    //***TO DO***  Look at arguments, open file, divide by threads
    //             Allocate and Initialize and storage structures
    // defining local variables
    int fDesc;
    int cPrc;
    infoOfChunk *iArr;
    pthread_t *pt;
    char *fname;
    // initializing filename, if there are no argumanets, these variables will work accordingly
    fname = "CSVTestFile.csv"; // Change this to the name of your CSV file
    cPrc = 1;
    // Conditional Statement
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    // Conditional Statement
    if (argc > 2)
    {
        fname = argv[1];
        cPrc = atoi(argv[2]);
    }
    // if arguments are passed, then initialized variables will get updated
    fDesc = open(fname, O_RDONLY);
    lseek(fDesc, 0, SEEK_END);
    long fileSize = lseek(fDesc, 0, SEEK_CUR);
    lseek(fDesc, 0, SEEK_SET);
    close(fDesc);

    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    //Time stamp start
    struct timespec startTime;
    struct timespec endTime;

    clock_gettime(CLOCK_REALTIME, &startTime);
    //**************************************************************
    // *** TO DO ***  start your thread processing
    //                wait for the threads to finish

    iArr = malloc(sizeof(infoOfChunk) * cPrc);
    pt = malloc(sizeof(pthread_t) * cPrc);
    // For Loop Statement
    for (int i = 0; i < cPrc; i++)
    {
        iArr[i].filename = fname;
        iArr[i].id = i + 1;
        iArr[i].start = (fileSize / cPrc) * i;
        if (i == cPrc - 1)
        {
            iArr[i].size = fileSize - iArr[i].start;
        }
        else
        {
            iArr[i].size = (fileSize / cPrc);
        }
        pthread_create(&(pt[i]), NULL, processChunk, &(iArr[i]));
    }
    // For Loop Statement
    for (int i = 0; i < cPrc; i++)
    {
        pthread_join(pt[i], NULL);
    }
    wordsEntryF topTenWords[TOP];
    // For Loop Statement
    for (int j = 0; j < TOP; j++)
    {
        topTenWords[j].count = 0;
    }
    // For Loop Statement
    for (int j = 0; j < counter2; j++)
    {
        // Conditional Statement
        if (wList[j].count > topTenWords[TOP - 1].count)
        {
            topTenWords[TOP - 1].word = wList[j].word;
            topTenWords[TOP - 1].count = wList[j].count;
            // Nested For Loop Statement
            for (int k = TOP - 2; k >= 0; k--)
            {
                // Conditional Statement
                if (wList[j].count > topTenWords[k].count)
                {
                    topTenWords[k + 1].word = topTenWords[k].word;
                    topTenWords[k + 1].count = topTenWords[k].count;
                    topTenWords[k].word = wList[j].word;
                    topTenWords[k].count = wList[j].count;
                }
            }
        }
    }

    // ***TO DO *** Process TOP 10 and display
    // Printing the Output
    printf("\n\nWord Frequency Count on %s with %d threads\n", fname, cPrc);
    printf("Printing top %d words %d characters or more. \n", TOP, MINIMUMCHARS);
    for (int k = 0; k < TOP; k++)
    {
        printf("Number %d is %s with a count of %d\n", k + 1, topTenWords[k].word, topTenWords[k].count);
    }

    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    // Clock output
    clock_gettime(CLOCK_REALTIME, &endTime);
    time_t sec = endTime.tv_sec - startTime.tv_sec;
    long n_sec = endTime.tv_nsec - startTime.tv_nsec;
    // Conditional Statement to calculate the time
    if (endTime.tv_nsec < startTime.tv_nsec)
    {
        --sec;
        n_sec = n_sec + 1000000000L;
    }

    printf("Total Time Was %ld.%09ld seconds\n", sec, n_sec);
    //**************************************************************
    // ***TO DO *** cleanup
    for (int j = 0; j < counter2; j++)
    {
        free(wList[j].word);
        wList[j].word = NULL;
    }
    free(wList);
    wList = NULL;
    pthread_mutex_destroy(&lock);
}
