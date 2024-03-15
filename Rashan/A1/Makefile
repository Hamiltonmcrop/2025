all: main

main.o: main.c
	gcc -c main.c

list.o: list.c
	gcc -c list.c

main: list.o main.o
	gcc -o main main.o list.o

clean:
	rm -f main *.o && clear

