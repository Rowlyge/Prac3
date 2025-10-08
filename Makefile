C=gcc
CFLAGS=-Wall -Wextra -std=c99

all: prog1 process

prog1: prog1.c
		$(CC) $(CFLAGS) -o prog1 prog1.c

process: process.c
		$(CC) $(CFLAGS) -o process process.c

clean:
		rm -f prog1 process output.txt

run: all
		./prog1

.PHONY: all clean run 
