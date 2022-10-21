#include "tp.h"
int forca_brutaII(int **grafo,int n){
  int  teste = 0,j=0;
  int * cvi;
  int * aux;
  cvi=(int*) malloc(sizeof(int)*n);//é alocado um vetor de tamanho do número de vértices
  //o while preenche cvi com os números de vértices
  while(j<n){
    cvi[j]=j;
    j++;
  }
  for(int i = n; i>1;i--){//i é o número de elementos presentes nos conjuntos, i vai de n a 2
    aux=(int*) malloc(sizeof(int)*i);//é alocado um vetor que será um conjunto de i elementos preenchido na função verificaCombinacoes
    teste=verificaCombinacoes(cvi,aux,0,n-1,0,i,grafo);//a função verificaCombinacoes verifica todas as funções procurando um conjunto que só tenha vértices independentes
    if(teste==1){//se a função verificarCOmbinacoes retorna 1 significa que algum conjunto de tamanho i só contem vértices independentes
      free(cvi);//libera cvi da mémoria 
      free(aux);//libera aux da mémoria
      return i;// retorna o tamanho do conjunto provado
    }
    free(aux);//libero aux da memoria
  }
  free(cvi);//libero cvi da memoria
  return 1;//caso nenhuma combinação é um conjunto independente de vértice é retornado 1
}
int verificaCombinacoes(int *elementos, int *cvi, int inicio, int fim, int tam, int k,int **grafo){
  int teste=0;
  if (tam == k){// se o tamanho do conjunto ser igual ao tamanho do conjunto pedido então uma combinação foi encontrada
    for (int j=0; j<k; j++){
      teste=verificarConjunto(cvi,k,grafo,cvi[j]);//chama a função verificarConjunto, para verificar se a combinação contem apenas vértices independentes
      if(teste==-1){
        return teste;// se em algum momento encontrar um vertice dependente é retornado teste = 0
      }
    }
    return 1;// se não encontrar vertices dependentes, então foi encontrado uma solução para o problema
  } 
  for (int i=inicio; i<=fim && fim-i+1 >= k-tam; i++){
    cvi[tam] = elementos[i];// o conjunto cvi, recebe i
    teste=verificaCombinacoes(elementos, cvi, i+1, fim, tam+1, k,grafo);//chama a função novamente incrementando 1 no inicio e no tamanho do conjunto
    if(teste==1){// se teste for igual a 1 significa que foi encontrado uma solução então é retornado teste = 1 em todas as funções são desimpilhads 
      return teste;//retorna teste = 1
    }
  }
  return teste; // se não encontrar solução é retornado teste que será diferente de 1
}
int verificarConjunto(int * cvi,int n,int **grafo,int v){
  for(int i = 0; i<n;i++){//o for percorre todo cvi
      if(grafo[cvi[i]][v]==1){//se na posição grafo[cvi[i]][v], ou seja na posição do vertice que está verificando com os outros vértices de cvi, existir 1,
        //retorna -1, significa que não é um conjunto independente de vertice por existir uma aresta entre algum dos elementos de cvi
        return -1;
      }    
  }
  //se não encontrar aresta retorna 1
  return 1;
}