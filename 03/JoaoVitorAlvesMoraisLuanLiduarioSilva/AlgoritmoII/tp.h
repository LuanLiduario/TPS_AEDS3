#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<math.h>
#include<unistd.h>
//struct utilizada para obter o vetor de numero de arestas
typedef struct{
    int vertice;
    int naresta;
}ContAresta;
//Assinaturas de funções
void lerArquivo(char *nomeArq,char *nomeSaida);
void escreverArquivo(int resultado,char *nomeSaida);

int **alocar_matriz(int vertices);
int ** insereAresta(int i,int j,int **grafo);
int **liberar_matriz (int vertices, int **matriz);
double tempo();

//guloso
void preencher(ContAresta* vetor,int nvertices);
int guloso(ContAresta *vetorArestas,int nvertices,int **grafo);
int verifica(int v,int ** grafo,int * cvi, int tamCvi);

//heap
void refazerVetorContAresta(int esq, int dir, ContAresta *a);
void construirVetorContAresta(ContAresta * a, int n);
void heapsortVetorContAresta(ContAresta *a, int n);

