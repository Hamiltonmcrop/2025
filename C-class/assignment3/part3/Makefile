CC = gcc
CFLAGS = -I. -w
DEPS = convert.h
OBJ = convert.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

convert: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
