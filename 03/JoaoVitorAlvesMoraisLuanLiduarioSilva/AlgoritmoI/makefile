all: main

main: tpmain.c arquivo.o forca_bruta.o grafo.o 
	gcc -O3 arquivo.o forca_bruta.o grafo.o tpmain.c -o main  -w

arquivo.o: arquivo.c tp.h
	gcc -O3 -c  arquivo.c  -w

forca_bruta.o: forca_bruta.c  tp.h
	gcc -O3 -c  forca_bruta.c  -w

grafo.o: grafo.c  tp.h
	gcc -O3 -c  grafo.c  -w

clear:
	rm *.o