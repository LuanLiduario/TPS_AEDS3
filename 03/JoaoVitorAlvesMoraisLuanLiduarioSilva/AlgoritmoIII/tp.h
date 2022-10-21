#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<math.h>
#include<unistd.h>
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
int gulosoII(ContAresta *vetorArestas,int nvertices,int **grafo);
void retirarAd(int v,ContAresta *vetorArestas,int *tam,int ** grafo,int nvertices);

//heap
void refazerVetorContAresta(int esq, int dir, ContAresta *a);
void construirVetorContAresta(ContAresta * a, int n);
void heapsortVetorContAresta(ContAresta *a, int n);

