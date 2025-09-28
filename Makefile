CC      = gcc
CFLAGS  = -Wall -Wextra -O2

all: prog1 prog2 my3proc

prog1: main.c
	$(CC) $(CFLAGS) main.c -o prog1

prog2: main2.c
	$(CC) $(CFLAGS) main2.c -o prog2

my3proc: main3.c
	$(CC) $(CFLAGS) main3.c -o my3proc

clean:
	rm -f prog1 prog2 my3proc