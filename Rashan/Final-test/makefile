CC=gcc
CFLAGS=-Wall -Wextra -g

main.out: main.c
	$(CC) $(CFLAGS) main.c -o main.out

test: main.out CSVTestFile.csv
	./main.out CSVTestFile.csv

clean:
	rm -f main.out

