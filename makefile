CC = gcc
CFLAGS = -Wall -g -std=c99

all: build

build:
	$(CC) $(CFLAGS) main.c list/list.c pcb.c commands/create.c commands/kill.c commands/exit.c commands/quantum.c commands/proc_info.c commands/total_info.c commands/send_recieve_reply.c commands/semaphores.c -o main
	
clean:
	rm -f main
