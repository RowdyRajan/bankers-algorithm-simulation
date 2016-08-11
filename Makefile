CC = gcc


run: build
	./a.out

build:
	$(CC) bankersAlogorithm.c

tar:
	tar cvf submit.tar bankersAlogorithm.c Makefile

