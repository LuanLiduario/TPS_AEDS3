all: main

main: tpmain.c arquivos.o guloso.o grafo.o pdinamica.o
	gcc -O3 arquivos.o guloso.o grafo.o pdinamica.o tpmain.c -o tp2  -w

arquivos.o: arquivos.c tp.h
	gcc -O3 -c  arquivos.c  -w

guloso.o: guloso.c  tp.h
	gcc -O3 -c  guloso.c  -w

grafo.o: grafo.c  tp.h
	gcc -O3 -c  grafo.c  -w

pdinamica.o: pdinamica.c  tp.h
	gcc -O3 -c  pdinamica.c  -w

clear:
	rm tp2 *.o