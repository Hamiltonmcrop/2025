 
#ifndef MAIN_H
 
#define MAIN_H
 
 
#include <stdio.h>
 
#include <string.h>
 
#include <stdlib.h>
 
#include <ctype.h>
 
 
typedef enum
 
{
 
    NONE = 0,       // No flags are passed in CLAs
 
    CLEAR = 1,      // -c
 
    HEX = 2,        // -x
 
    SCIENTIFIC = 4, // -e
 
    TRUNCATED = 8   // -s
 
} flags;
 
 
char *strip(char *input);
 
int is_int(char *input);
 
int is_double(char *input);
 
 
#endif // CONVERT_H
 

