#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<math.h>
#include<unistd.h>
//Assinaturas de funções
void lerArquivo(char *nomeArq,char *nomeSaida);
int **alocar_matriz(int vertices);
int ** insereAresta(int i,int j,int **grafo);
void printMatriz(int v,int **grafo);
int **liberar_matriz (int vertices, int **matriz);
double tempo();

//Assinaturas de funções especificas desse algoritmo
int forca_brutaII(int **grafo,int n);
int verificarConjunto(int * cvi,int n,int **grafo,int v);
int verificaCombinacoes(int *elementos, int *cvi, int inicio, int fim, int tam, int k,int **grafo);
