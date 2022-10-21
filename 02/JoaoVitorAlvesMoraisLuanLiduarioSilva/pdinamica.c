#include "tp.h"
void matrizD (int vertices, int **adjacente, valores *resultados){
    distancia **distM = (distancia **) calloc (vertices+1, sizeof(distancia *)); //alocando a matriz
    for ( int i = 0; i < vertices+1; i++ ) {
        distM[i] = (distancia*) calloc (vertices+1, sizeof(distancia));   
    }

    for(int i =1; i<=vertices; i++){
        for(int j=1; j<=vertices; j++){
            distM[i][j].caminho = (int *) calloc (vertices, sizeof(int));
            distM[i][j].tamCaminho = 0;
            if(i==j){
                distM[i][j].dist= 0;
            }else{
                if(adjacente[i-1][j-1]!=0){
                    distM[i][j].dist = adjacente[i-1][j-1];
                }else{
                     distM[i][j].dist = 999999999;
                }
            }
        }
    }

    for(int k=1; k<= vertices; k++){
        for(int i =1; i<=vertices; i++){
            for(int j=1; j<= vertices; j++){
                if(distM[i][j].dist > distM[i][k].dist + distM[k][j].dist){
                    distM[i][j].dist = distM[i][k].dist + distM[k][j].dist;
                    distM[i][j].tamCaminho = distM[i][k].tamCaminho + distM[k][j].tamCaminho + 1;
                    for(int l =0; l<distM[i][k].tamCaminho; l++){
                        distM[i][j].caminho[l] = distM[i][k].caminho[l];
                    }

                    distM[i][j].caminho[distM[i][j].tamCaminho - 1] = k;

                    for(int l = distM[i][k].tamCaminho; l<distM[i][j].tamCaminho; l++){
                        distM[i][j].caminho[l] = distM[k][j].caminho[l - distM[i][k].tamCaminho];
                    }
                }
            }
        }
    }
    for(int i =1; i<=vertices; i++){
        printf("\n");
        for(int j=1; j<= vertices; j++){
            printf("%d ", distM[i][j].dist);
        }
    }
    for(int i =1; i<=vertices; i++){
        printf("\n");
        for(int j=1; j<= vertices; j++){
            printf("\n%d,%d ", i,j);
            for(int l=1; l<= distM[i][j].tamCaminho; l++){
            printf("%d-", distM[i][j].caminho[l]);
        }
        }
    }
}


valores* mochilaInteira(int capacidade, int qtdItens, Povo *povos){
    valores *resultados = (valores *) calloc (capacidade+1, sizeof(valores));
    for(int i = 0; i<capacidade+1; i++){
        resultados[i].qtd = (int *) calloc (qtdItens, sizeof(int));
        resultados[i].valor = 0;
    }
    for(int i = 0; i<=capacidade; i++){
        for(int j = 0; j<qtdItens; j++){
            if(povos[j].peso <= i){
                if(resultados[i].valor < (resultados[i-povos[j].peso].valor + povos[j].habilidade)){
                    resultados[i].valor = resultados[i-povos[j].peso].valor + povos[j].habilidade;
                    for(int k=0; k<qtdItens; k++){
                        resultados[i].qtd[k] = resultados[i-povos[j].peso].qtd[k];
                    }
                    resultados[i].qtd[j]=resultados[i].qtd[j]+1;
                }
            }
        }
    }

    return resultados;
}