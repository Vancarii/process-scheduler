CC = gcc
CFLAGS = -Wall -g -std=c99

all: build

build:
	$(CC) $(CFLAGS) main.c list/list.c
	
clean:
	rm -f a.out
