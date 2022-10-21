#include "tp.h"
//GULOSO II
int gulosoII(ContAresta *vetorArestas,int nvertices,int **grafo){
    int tam= nvertices;//tam recebe o número de vértices presentes no grafo, ou seja assume que todos os vértices são independentes
    for(int i = 0; i < nvertices; i++){// percorre vetorArestas partindo da posição 0
        if(vetorArestas[i].naresta>0 ){// caso o número de arestas da posição i for 0, ele não necessita de verificação, pois ele será independente, se for -1, significa que o vértice foi retirado da solução
            retirarAd(i,vetorArestas,&tam,grafo,nvertices);//retira os adjascentes do vertice na posição i
        }
    }
    return tam; // retorna tam, tam é decrementado durante a função retiraAd
}

void retirarAd(int v,ContAresta *vetorArestas,int *tam,int ** grafo,int nvertices){
    int i = 0;
    int j = nvertices-1;
    while(i<vetorArestas[v].naresta){//percorre vetorArestas,partindo da sua ultima posição para a primeira,
    // pois como o ultima posição tem mais arestas, é o vertice mais provavel ter aresta para o vertice da posição v. 
    //O vetor é percorrido até encontrar todos os adjascentes do vertice da posição v
        if(grafo[vetorArestas[v].vertice][vetorArestas[j].vertice]==1){//se existir aresta entre o vertice da posição v e o da posição i, é incrementado 1 no contador
            //que conta a quantidade de adjascentes encontrados
            i++;
            if(vetorArestas[j].naresta!=-1){// se o adjascente encontrado tiver o número de arestas -1, significa que ele já foi retirado da solução
                vetorArestas[j].naresta=-1;//se for diferente de -1, o número de aresta recebe -1, ou seja retira da solução
                (*tam)--;// tam é decrementado, ou seja diminui o tamanho do conjunto solução
            }
        }
        j--;    
    }
}
void preencher(ContAresta* vetor,int nvertices){
    for(int i=0;i<nvertices;i++){//percorre o vetor 
        vetor[i].vertice=i;// o vetor na posição i, variavel vertice recebe i, para salvar o número do vértice
        vetor[i].naresta=0;// todas os números de arestas recebem 0
    }
}