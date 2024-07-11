CC = gcc
CFLAGS = -I. -w -pthread
DEPS = hash.h
OBJ = hashset.c passwordgen.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

passgenerator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lm

