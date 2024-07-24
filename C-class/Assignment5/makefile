CC=gcc
CFLAGS=-I. -g -w -pthread -lm -Wno-implicit-function-declaration
DEPS= solve.h
OBJ = solver.o hashset.o btree.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
solve: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)