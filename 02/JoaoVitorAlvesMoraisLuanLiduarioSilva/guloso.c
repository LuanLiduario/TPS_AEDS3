#include "tp.h"
void guloso(int ** grafo,Povo *vetor,int povos,int distanciaMAX,int w,FILE *arqSaida){
    int noInicial,qtd;
    int habilidadeFinal=0;
    //no Inicial recebe o povo com maior razão h/p
    noInicial=maiorRazao(vetor,povos);
    //qtd recebe a quantidade de soldados do povo inicial que será adicionado na solução
    qtd=preencher(vetor[noInicial].peso,w);
    //Marco o no Inicial como visitado
    vetor[noInicial].visitado=-1;
    //É subtraido do peso maximo o peso do povo inicial * quantidade de soldados recrutados
    w=w-(qtd*vetor[noInicial].peso);
    //habilidade final recebe a soma dele mesmo com a habilidade do povo * qtd
    habilidadeFinal=habilidadeFinal+(qtd*vetor[noInicial].habilidade);
    int *resultado;
    int i =3;
    //inicialmente é alocado um vetor de 3 posições, pois na posição 0 o vetor sempre terá a habilidade final, nas posições impares 
    //o vetor terá o número do povo que está na solução e nas pares a quantidade dos povos
    resultado=(int*)malloc(i*sizeof(int));
    resultado[0]=habilidadeFinal;
    resultado[1]=vetor[noInicial].povo;
    resultado[2]=qtd;
 	int t=0;
 	while(qtd>0 && t!=-1 && distanciaMAX > 0){
        // quando t for -1 significa que não encontrou nenhum adjascentes que passam por todas as condições
 		t=encontrarAdjacente(vetor,noInicial,distanciaMAX,povos,grafo,w);
	    if(t!=-1){
            //A cada adjascente adicionado a solução é repetido o processo do inicial
	    	 qtd=preencher(vetor[t].peso,w);
	   		 vetor[t].visitado=-1;
	    	 w=w-(qtd*vetor[t].peso);
	    	 habilidadeFinal=habilidadeFinal+(qtd*vetor[t].habilidade);
             //É alocado mais dois espaços no vetor de solução
             //A primeira posição alocada recebe o povo e a segunda a quantidade do povo
	    	 i=i+2;
	    	 resultado=realloc( resultado, i * sizeof(int) );
	    	 resultado[i-2]=vetor[t].povo;
	    	 resultado[i-1]=qtd;
	    	 resultado[0]=habilidadeFinal;
	    	 distanciaMAX=distanciaMAX-grafo[noInicial][t];
             //o povo encontrado se torna o povo inicial
	    	 noInicial=t;
	    }
	}
    //chama a função escreverArquivo para escrever a solução no arquivo
	escreverArquivo(resultado,i,arqSaida);
}

int maiorRazao(Povo *vetor,int povos){
    float razao=0;// h/w
    float razaoAnterior=-1;// h/w
    int max=-1;
    //O for percorre o vetor de povos recebido
    for (int  j=0; j<povos; j++ ){
        razao=((float)vetor[j].habilidade)/((float)vetor[j].peso);
        if(razao>razaoAnterior){
            //verifica se a razão atual é maior que a anterior
            max=j;
            //se for max recebe a posição j e razaoAnterio recebe a razão atual
            razaoAnterior=razao;
        }
        if(razao==razaoAnterior && vetor[j].habilidade>vetor[max].habilidade){
            //se a razão for igual, és escolhido o povo com maior habiliade
        	max=j;
           	razaoAnterior=razao;
        }
    }
    //retorna a posição da maior razão
    return max;
}

int preencher(int peso,int w){
    int qtd =0;
    //qtd vai receber a parte inteira da divisão de w/p
    float razao =0;
    razao=(float)w/(float)peso;
    qtd= (int)razao;
   return qtd;
}

int encontrarAdjacente(Povo *vetor,int povoi,int distanciaMAX,int povos,int **grafo, int w){
	int i=0;
	Povo *vetor_adjacentes;
	vetor_adjacentes= (Povo*)malloc(sizeof(Povo));
    //i é a quantidade de adjascente que passa por todas as condições e o vetor_adjascente receberá os povos que são adjascentes 
    for (int  j=0; j<povos; j++ ){ 
        //percorremos o vetor de povos
            if(grafo[povoi][j]!=0 && vetor[j].visitado!=-1 && w>= vetor[j].peso && grafo[povoi][j]<=distanciaMAX){
                //se houver caminho entre os povos, se não tiver sido visitado, se o peso cabe na peso maximo e a distância for menor igual a distância máxima
                //será alocado mais uma posição no vetor, o vetor vai receber o povo
                //e o i vai somar 
                vetor_adjacentes=realloc( vetor_adjacentes, (i +1) * sizeof(Povo) );
                vetor_adjacentes[i]=vetor[j];
                i++;
            }
        

    }
    int maior_adjastecente=-1;
    if(i==0){
        //se não encontrar nenhum adjascente a função retorna -1
    	free(vetor_adjacentes);
    	return -1;
    }
    //maiorRazão vai retorna qual dos adjascentes tem a maior razão
    maior_adjastecente=maiorRazao(vetor_adjacentes,i);
    maior_adjastecente=vetor_adjacentes[maior_adjastecente].povo - 1;
    free(vetor_adjacentes);
    return maior_adjastecente;
    
}