#include "tp.h"
//Guloso I
int guloso(ContAresta *vetorArestas,int nvertices,int **grafo){
    int * cvi;
    cvi=(int*) malloc(sizeof(int)*nvertices);//aloca um vetor de inteiros de nvertices posições
    int tam=1,aux=1;
    cvi[0]=vetorArestas[0].vertice;//a primeira posição de cvi recebe o vertice que esta na primeira posição do 
    for(int i = 1; i < nvertices; i++){//percorre o vetor vetorArestas
        if(vetorArestas[i].naresta==0){//se o vertice não tiver aresta ele pode ser adicionado no conjunto solução
            cvi[tam]=vetorArestas[i].vertice;//o cvi recebe na posição tam o vertice do vetorAresta na posição i
            tam++;// tam é incrementado
        }else{
            aux=verifica(vetorArestas[i].vertice,grafo,cvi,tam);//aux recebe 0 se o vertice verificado não tem aresta pros vertices que estão em cvi
            if(aux==0){
                cvi[tam]=vetorArestas[i].vertice;//o cvi recebe na posição tam o vertice do vetorAresta na posição i
                tam++;// tam é incrementado
            }
        }
    }
    free(cvi);//libero cvi da memoria
    return tam;//retorno o tam  que é o tamanho de cvi
}
void preencher(ContAresta* vetor,int nvertices){
    for(int i=0;i<nvertices;i++){//percorre o vetor 
        vetor[i].vertice=i;// o vetor na posição i, variavel vertice recebe i, para salvar o número do vértice
        vetor[i].naresta=0;// todas os números de arestas recebem 0
    }
}
int verifica(int v,int ** grafo,int * cvi, int tamCvi){
    int i=0;
    while(i<tamCvi){//percorre o vetor cvi
       if(grafo[v][cvi[i]]==1){//se existir aresta entre o vertice v e o vertice na posição i de cvi, então essa posição no grafo será 1
            return -1; //se existe aresta, retorna -1
        }
        i++; 
    }
    return 0;//se não encontrar nenhuma aresta de v com os vertices de cvi retorna 0
}
