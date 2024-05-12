all: greetings
greetings: hello.o bye.o main.o
	gcc -o greetings hello.o bye.o main.o -Wall -Werror
hello.o: hello.c main.h
	gcc -c hello.c
bye.o: bye.c main.h
	gcc -c bye.c
main.o: main.c main.h
	gcc -c main.c
clean:
	rm -f *.o greetings

