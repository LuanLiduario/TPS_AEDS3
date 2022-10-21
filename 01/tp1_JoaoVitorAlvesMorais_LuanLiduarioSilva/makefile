all: main clear

main: tp.o tpmain.o
	gcc tp.o tpmain.o -o main -lm

tpmain.o: tpmain.c tp.h
	gcc -g -c tpmain.c 

tp.o: tp.c tp.h
	gcc -g -c tp.c

clear:
	rm *.o