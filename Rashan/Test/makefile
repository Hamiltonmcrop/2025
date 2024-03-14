CC=gcc
CFLAGS=-Wall -Wextra -g

Chou_Tina_HW4: Chou_Tina_HW4.c
	$(CC) $(CFLAGS) Chou_Tina_HW4.c -o Chou_Tina_HW4

test: Chou_Tina_HW4 CSVTestFile.csv
	./Chou_Tina_HW4 CSVTestFile.csv

clean:
	rm -f Chou_Tina_HW4
