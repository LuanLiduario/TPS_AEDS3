#include "tp.h"
//Grafos
int ** insereAresta(int i,int j,int **grafo){
    //Atribui a aresta na matriz
    grafo[i][j]=1;
    grafo[j][i]=1;
    return grafo;
}
int **alocar_matriz(int vertices){
  int **matriz;  // ponteiro para a matriz 
  // aloca as linhas da matriz 
  matriz = (int **) calloc (vertices, sizeof(int *));   // Um vetor de vertices ponteiros para int
  // aloca as colunas da matriz 
  for ( int i = 0; i < vertices; i++ ) {
      matriz[i] = (int*) calloc (vertices, sizeof(int));    // vertices vetores de int 
      }
  return (matriz); // retorna o ponteiro para a matriz 
}
int **liberar_matriz (int vertices, int **matriz){
  if (matriz == NULL) return (NULL);
  for (int i=0; i<vertices; i++) free (matriz[i]); // libera as linhas da matriz 
  free (matriz);      // libera a matriz (vetor de ponteiros) 
  return (NULL); // retorna um ponteiro nulo 
}