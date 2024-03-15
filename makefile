CC = gcc
CFLAGS = -Wall -g -std=c99

all: build

build:
	$(CC) $(CFLAGS) main.c list/list.c pcb.c commands/create.c commands/kill.c commands/exit.c -o main
	
clean:
	rm -f main
