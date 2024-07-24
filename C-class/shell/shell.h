 
#include <stdio.h>
 
#include <stdlib.h>
 
#include <unistd.h>
 
#include <string.h>
 
#include <math.h>
 
#include <sys/wait.h>
 
#include <dirent.h> 
 
#define error(m,c) do { fprintf(stderr, "%s\n", m); exit(c); } while (0)
 
#define MAX_INPUT_SIZE 4096
 
#define IPC_BUF_SIZE 4096

