# makefile

CC = gcc
CFLAGS = -g -Wall

project1: func.o main.o
	$(CC) $(CFLAGS) -o project1 func.o main.o

func.o: func.c func.h
	$(CC) $(CFLAGS) -c func.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm func.o main.o project1