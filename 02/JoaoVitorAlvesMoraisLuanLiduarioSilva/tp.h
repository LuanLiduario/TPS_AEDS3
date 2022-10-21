#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>
//#include<math.h>
#include<unistd.h>
typedef struct{
    //Criando a estrutura 
    int peso;
    int habilidade;
    int visitado;
    int povo;
    
}Povo;//Vertices
typedef struct{
    int valor;
    int *caminho;
    int *qtd;
}valores;
typedef struct{
    int dist;//menor distancia
    int *caminho;
    int tamCaminho;
}distancia;

int ** insereAresta(int povoi,int povoj,int distanciaij,int **grafo);
int **Alocar_matriz(int vertices);
void printMatriz(int n,int ** matriz);
int **Liberar_matriz (int vertices, int **matriz);
void guloso(int ** grafo,Povo *vetor,int povos,int distanciaMAX,int w,FILE *arqSaida);
double tempo();
void lerArquivo(char *nomeArq,char *nomeSaida);
void escreverArquivo(int *caminho,int i,FILE *arqSaida);
int maiorRazao(Povo *vetor,int povos);
int preencher(int peso,int w);
int encontrarAdjacente(Povo *vetor,int povoi,int distanciaMAX,int povos,int **grafo, int w);
valores* mochilaInteira(int capacidade, int qtdItens, Povo *povos);
void matrizD (int vertices, int **adjacente, valores *resultados);



