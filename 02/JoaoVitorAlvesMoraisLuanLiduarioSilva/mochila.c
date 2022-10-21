#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<math.h>
#include<unistd.h>
typedef struct{
    //Criando a estrutura 
    int peso;
    int habilidade;
    int visitado;
    int povo;
    
}Povo;

typedef struct{
    int valor;
    int *caminho;
    int *qtd;
}valores;



//capacidade = w; qtdItens = numero de povos = p;

valores **matrizR (int capacidade, int qtdItens, Povo *povos){

    valores **resultados = (valores **) calloc (qtdItens+1, sizeof(valores *)); //alocando a matriz
    for ( int i = 0; i < qtdItens+1; i++ ) {
        resultados[i] = (valores*) calloc (capacidade+1, sizeof(valores));   
    }

    for (int j= 0; j<capacidade;j++){//colocando 0 em toda a coluna 0
        resultados[0][j].valor = 0;

        resultados[0][j].caminho = (int*) calloc (1, sizeof(int));
        resultados[0][j].caminho[0] = 0;

        resultados[0][j].qtd = (int*) calloc (1, sizeof(int));
        resultados[0][j].qtd[0] = 0;

    }
    
    for (int i=0; i< qtdItens; i++){//colocando 0 em toda a linha 0
        resultados[i][0].valor = 0;

        resultados[i][0].caminho = (int*) calloc (1, sizeof(int));
        resultados[i][0].caminho[0] = 0;

        resultados[i][0].qtd = (int*) calloc (1, sizeof(int));
        resultados[i][0].qtd[0] = 0;
    }

    int aux = 0, auxP =0, auxQ = 0; //definindo um auxiliar pra valor, peso e quantidade

    for (int i = 1; i<=qtdItens; i++){//laço pra percorrer a matriz e preenchê-la
        for (int j = 1; j<=capacidade; j++){
            resultados[i][j].caminho = (int*) calloc (i, sizeof(int));//alocando o vetor de caminho da strcut valores na posição atual da matriz
            resultados[i][j].qtd = (int*) calloc (i, sizeof(int));//alocando o vetor de quantidade da strcut valores na posição atual da matriz

            if(j>= povos[i].peso){//caso o povo caiba pelo menos uma vez na quantidade de peso analisada
                aux = 0;
                auxP = 0;
                auxQ = 0;

                while(auxP<=j){//enquanto couber o povo...
                  aux = aux + povos[i].habilidade;//...soma a sua habilidade mais uma vez
                  auxP = auxP + povos[i].peso; //... soma o seu peso mais uma vez
                  auxQ = auxQ + 1;//... e aumenta 1 na quantidade que está entrando nave   
                }

                if(auxP>j){//se o peso ultrapassar o limite analisado é necessário voltar ao valor anterior de peso e quantidade
                    auxP = auxP - povos[i].peso;
                    auxQ = auxQ - 1;
                }

                aux = aux + resultados[i-1][j-auxP].valor;// soma o melhor valor pro peso ainda disponível (que está na linha de cima da matriz)

                if (aux > resultados[i-1][j].valor){//comparo a minha soma com o melhor valor já analisado pra aquela quantidade em questão (linha de cima e mesma coluna)
                    //caso a minha soma seja maior
                    resultados[i][j].valor = aux;//o valor da posição atual da minha matriz será a mina soma
                    resultados[i][j].caminho[0] = i;//adiciono o povo no vetor de caminho
                    resultados[i][j].qtd[0] = auxQ;//adiciono a quantidade desse povo

                    for(int a = 0; a<i-1; a++){//percorre-se o vetor de caminho e quantidade da posiçao da matriz que entrou na soma do meu valor
                        resultados[i][j].caminho[a+1] =  resultados[i-1][j-auxP].caminho[a];// o vetor de caminho e quantidade da posiçao em questão são adicionados no final dos vetores da posição atual
                        resultados[i][j].qtd[a+1] =  resultados[i-1][j-auxP].qtd[a];
                    }

                }else{//caso a minha soma seja menor
                    resultados[i][j] = resultados[i-1][j]; //o elemento da linha de cima na mesma coluna é copiado para a posição atual
                }
            }else{//caso o povo nao caba nenhuma vez na quantidade analisada
                resultados[i][j] = resultados [i-1][j];//o elemento da linha de cima na mesma coluna é copiado para a posição atual
            } 
        }
    }

    
    return (resultados);
}