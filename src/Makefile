# makefile for dynamic library

CC = gcc

app.out: main.c ../lib/src/func.h
	$(CC) -fPIC -c ../lib/src/func.c -o ../lib/dynamic/func.o 
	$(CC) -shared -o ../lib/dynamic/libfunc.so ../lib/dynamic/func.o 
	$(CC) main.c -L../lib/dynamic/ -lfunc -o ../bin/app.out

clean:
	rm -f ../lib/dynamic/func.o ../lib/dynamic/libfunc.so ../bin/app.out
