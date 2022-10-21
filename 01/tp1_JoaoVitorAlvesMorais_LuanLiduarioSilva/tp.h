#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<math.h>
#include<unistd.h>

//Assinaturas de funções
void lerArquivo(char *nomeArq,char *nomeSaida);
long long int fatorar(long long int n);
long long int calcXulambs (long long int n);
long long int fatorial (long long int n);
void escreverArquivo(char *nomeArq,long long int *listaR,int i);
double tempo();
long long int* crivoEratostenes();
long long int qtdPrimos(long long int n,long long int* lista);

