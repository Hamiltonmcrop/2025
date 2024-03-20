CC = gcc
CFLAGS = -g -Wall

all: main

main: main.o list.o
	$(CC) $(CFLAGS) -o main main.o list.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

clean:
	-rm main main.o list.o
