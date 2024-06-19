CFLAGS=-Wall -Wextra

all:
	cc main.c patterns.c graphics.c game.c $(CFLAGS) -lSDL2 -o gol

output: main.o patterns.o graphics.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c patterns.h graphics.h
	$(CC) $(CFLAGS) -c $< -o $@

patterns.o: patterns.c patterns.h
	$(CC) $(CFLAGS) -c $< -o $@

graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) -c $< -o $@ -lSDL2

clean:
	rm -f output main.o patterns.o graphics.o
