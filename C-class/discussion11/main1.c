#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#define lrand() (rand() * 2147483648L + rand())
// This program receives a file name as its only command-line argument
// It shuffles the content of the file randomly using low-level I/O
// Uses the following Unix system calls: read, write, open, lseek, close
int main(int argc, char *argv[])
{
    srand(time(NULL)); // to initialize rand and lrand so that they can properly
                       // generate random numbers.
    int fd = open(argv[1], O_RDWR);
    long file_size = lseek(fd, 0, SEEK_END); // find the file size
    fprintf(stderr, "The file size is %ld bytes!\n", file_size);
    lseek(fd, 0, SEEK_SET); // rewind
    for (long i = 0; i < file_size / 2; i++)
    {
        long j = file_size - 1 - i;
        fprintf(stderr, "Swapped chars at index %ld and %ld.\n", i, j);
        char from, to;
        read(fd, &from, 1);
        lseek(fd, j, SEEK_SET);
        read(fd, &to, 1);
        lseek(fd, j, SEEK_SET);
        write(fd, &from, 1);
        lseek(fd, i, SEEK_SET);
        write(fd, &to, 1);
    }
    close(fd);
}
