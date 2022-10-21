all: main

main: tpmain.c arquivo.o guloso.o grafo.o heapsort.o
	gcc -O3 arquivo.o guloso.o grafo.o heapsort.o tpmain.c -o main  -w

arquivo.o: arquivo.c tp.h
	gcc -O3 -c  arquivo.c  -w

guloso.o: guloso.c  tp.h
	gcc -O3 -c  guloso.c  -w

grafo.o: grafo.c  tp.h
	gcc -O3 -c  grafo.c  -w

heapsort.o: heapsort.c  tp.h
	gcc -O3 -c  heapsort.c  -w

clear:
	rm *.o