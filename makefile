CC = gcc
CFLAGS = -Wall -g -std=c99

all: build

build:
	$(CC) $(CFLAGS) main.c list/list.c -o main
	
clean:
	rm -f main
