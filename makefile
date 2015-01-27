all: zll.o test

zll.o: zll.c
	gcc zll.c -c -o zll.o
	
test: test.c
	gcc test.c zll.o -o test
