CC=gcc
CFLAGS=-Wall -Wextra

output: main.o patterns.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c patterns.h
	$(CC) $(CFLAGS) -c $< -o $@

patterns.o: patterns.c patterns.o
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f output main.o patterns.o