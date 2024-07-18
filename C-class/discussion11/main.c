#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#define lrand() (rand() * 2147483648L + rand ())

int main(int arg,char* argv[]){

	srand(time(NULL));
	int fd = open(argv[1],O_RDWR);
	long file_size=lseek(fd,0,SEEK_END);
	fprintf(stderr,"The file size is %ld bytes!\n",file_size);
	lseek(fd,0,SEEK_SET);
	for (long i=0; i < file_size-1;i++){
		long loc = lrand()%(file_size-i)+i;
		fprintf(stderr,"Swapped chars at index %ld and %ld.\n",i,loc);
		char from, to;
	       read(fd,&from,1);
	       lseek(fd,loc,SEEK_SET);
	       read(fd,&to,1);
	       lseek(fd,loc,SEEK_SET);
	       write(fd,&from,1);
	       lseek(fd,i,SEEK_SET);
	       write(fd,&to,1);
	}
	close(fd);
}
