CC = gcc


run: build
	./a.out

build:
	$(CC) assign3.c

tar:
	tar cvf submit.tar assign3.c Makefile

