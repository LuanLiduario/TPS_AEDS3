#include "tp.h"
//Arquivo de opera��es em arquivos
void lerArquivo(char *nomeArq,char *nomeSaida){
    //Abre o arquivo de texto
    FILE *arq = fopen(nomeArq, "r");
    FILE *arqSaida = fopen(nomeSaida, "w");
    if(arq == NULL){ 
        printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
        return;
    };
    char c;
    char linha[50];
    int n;  //Numero de instancias
    fgets(linha,50,arq);
    n=atoi(linha);
    //Leio Quantidade de instancias
    strcpy(linha, "");
    //v�riveis utilizadas em cada instancia 
    int i,k,p,d,w,ncaminhos,x,povoj,distanciaij;
    int **grafo;
    Povo *vetor_povo=NULL;
    for(int instancias=0;instancias<n;instancias++){
        i=0;
        k=0;
        p=0;
        d=0;
        w=0;
        ncaminhos=0;
        x=0;
        povoj =0;
        distanciaij=0;
        //Ler propriedades da instancia
        while(c!='\n'){
            c=getc(arq);
            linha[i]=c;
            i++;
            if(c==' '){
                linha[i] = '\0';
                x= atoi(linha);
                strcpy(linha, ""); 
                c='y';
                i=0;
                if(k==0){
                    p = x;
                }else if(k==1){
                    d = x;
                }else if(k == 2){
                    w = x;
                }
                k++;
            }
        }
        linha[i] = '\0';
        x= atoi(linha);
        strcpy(linha, ""); 
        c='y';
        i=0;
        ncaminhos=x;
        k=0;
        vetor_povo=(Povo*) calloc (p, sizeof(Povo));  
        grafo=Alocar_matriz(p);
        //Ler Povos
        int povoi = 0,wi = 0,hi=0;
        for(int j=0;j<p;j++){
            while(c!='\n'){
            c=getc(arq);
            linha[i]=c;
            i++;
            if(c==' '){
                linha[i] = '\0';
                x= atoi(linha);
                strcpy(linha, ""); 
                c='y';
                i=0;
                if(k==0){
                    vetor_povo[j].povo= x;
                }else if(k==1){
                    vetor_povo[j].peso = x;
                }
                k++;
            }
        }
        linha[i] = '\0';
        x= atoi(linha);
        strcpy(linha, ""); 
        c='y';
        i=0;
        vetor_povo[j].habilidade=x;
        k=0;
        }
        //Ler Caminhos
        for(int j=0;j<ncaminhos;j++){
            while(c!='\n' && !feof(arq)){
            c=getc(arq);
            linha[i]=c;
            i++;
            if(c==' '){
                linha[i] = '\0';
                x= atoi(linha);
                strcpy(linha, ""); 
                c='y';
                i=0;
                if(k==0){
                    povoi = x;
                }else if(k==1){
                    povoj = x;
                }
                k++;
            }
        }
        linha[i] = '\0';
        x= atoi(linha);
        strcpy(linha, ""); 
        c='y';
        i=0;
        distanciaij=x;
        k=0;
        grafo=insereAresta(povoi,povoj,distanciaij,grafo);
        }
        //matrizD(p,grafo,mochilaInteira(w,p,vetor_povo));
        guloso(grafo,vetor_povo,p,d,w,arqSaida);
        free(vetor_povo);
        grafo=Liberar_matriz(p,grafo);
}
    //Fecha os arquivos
    fclose(arq);
    fclose(arqSaida);

}
void escreverArquivo(int *caminho,int i,FILE *arqSaida){
    //Abre o arquivo de texto
    if(arqSaida == NULL) printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
    char linha[100]; 
    //Percorre o vetor recebido, a cada posi��o do vetor � escrito na linha no arquivo
    for(int j=0;j<i;j++){
        fprintf(arqSaida, "%d",caminho[j]);
        fprintf(arqSaida, "%s"," ");
        
    }
    fprintf(arqSaida, "%s","\n");
}
// Arquivo Grafos
//Grafos

int ** insereAresta(int povoi,int povoj,int distanciaij,int **grafo){
    //Atribui a dist�ncia na matriz
    grafo[povoi-1][povoj-1]=distanciaij;
    grafo[povoj-1][povoi-1]=distanciaij;
    return grafo;
}

int **Alocar_matriz(int vertices){
  int **matriz;  /* ponteiro para a matriz */
  /* aloca as linhas da matriz */
  matriz = (int **) calloc (vertices, sizeof(int *));   // Um vetor de vertices ponteiros para int
  /* aloca as colunas da matriz */
  for ( int i = 0; i < vertices; i++ ) {
      matriz[i] = (int*) calloc (vertices, sizeof(int));    /* vertices vetores de int */
      }
  return (matriz); /* retorna o ponteiro para a matriz */
}
int **Liberar_matriz (int vertices, int **matriz){
  if (matriz == NULL) return (NULL);
  for (int i=0; i<vertices; i++) free (matriz[i]); /* libera as linhas da matriz */
  free (matriz);      /* libera a matriz (vetor de ponteiros) */
  return (NULL); /* retorna um ponteiro nulo */
}
void guloso(int ** grafo,Povo *vetor,int povos,int distanciaMAX,int w,FILE *arqSaida){
    int noInicial,qtd;
    int habilidadeFinal=0;
    //no Inicial recebe o povo com maior raz�o h/p
    noInicial=maiorRazao(vetor,povos);
    //qtd recebe a quantidade de soldados do povo inicial que ser� adicionado na solu��o
    qtd=preencher(vetor[noInicial].peso,w);
    //Marco o no Inicial como visitado
    vetor[noInicial].visitado=-1;
    //� subtraido do peso maximo o peso do povo inicial * quantidade de soldados recrutados
    w=w-(qtd*vetor[noInicial].peso);
    //habilidade final recebe a soma dele mesmo com a habilidade do povo * qtd
    habilidadeFinal=habilidadeFinal+(qtd*vetor[noInicial].habilidade);
    int *resultado;
    int i =3;
    //inicialmente � alocado um vetor de 3 posi��es, pois na posi��o 0 o vetor sempre ter� a habilidade final, nas posi��es impares 
    //o vetor ter� o n�mero do povo que est� na solu��o e nas pares a quantidade dos povos
    resultado=(int*)malloc(i*sizeof(int));
    resultado[0]=habilidadeFinal;
    resultado[1]=vetor[noInicial].povo;
    resultado[2]=qtd;
 	int t=0;
 	while(qtd>0 && t!=-1 && distanciaMAX > 0){
        // quando t for -1 significa que n�o encontrou nenhum adjascentes que passam por todas as condi��es
 		t=encontrarAdjacente(vetor,noInicial,distanciaMAX,povos,grafo,w);
	    if(t!=-1){
            //A cada adjascente adicionado a solu��o � repetido o processo do inicial
	    	 qtd=preencher(vetor[t].peso,w);
	   		 vetor[t].visitado=-1;
	    	 w=w-(qtd*vetor[t].peso);
	    	 habilidadeFinal=habilidadeFinal+(qtd*vetor[t].habilidade);
             //� alocado mais dois espa�os no vetor de solu��o
             //A primeira posi��o alocada recebe o povo e a segunda a quantidade do povo
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
    //chama a fun��o escreverArquivo para escrever a solu��o no arquivo
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
            //verifica se a raz�o atual � maior que a anterior
            max=j;
            //se for max recebe a posi��o j e razaoAnterio recebe a raz�o atual
            razaoAnterior=razao;
        }
        if(razao==razaoAnterior && vetor[j].habilidade>vetor[max].habilidade){
            //se a raz�o for igual, �s escolhido o povo com maior habiliade
        	max=j;
           	razaoAnterior=razao;
        }
    }
    //retorna a posi��o da maior raz�o
    return max;
}

int preencher(int peso,int w){
    int qtd =0;
    //qtd vai receber a parte inteira da divis�o de w/p
    float razao =0;
    razao=(float)w/(float)peso;
    qtd= (int)razao;
   return qtd;
}

int encontrarAdjacente(Povo *vetor,int povoi,int distanciaMAX,int povos,int **grafo, int w){
	int i=0;
	Povo *vetor_adjacentes;
	vetor_adjacentes= (Povo*)malloc(sizeof(Povo));
    //i � a quantidade de adjascente que passa por todas as condi��es e o vetor_adjascente receber� os povos que s�o adjascentes 
    for (int  j=0; j<povos; j++ ){ 
        //percorremos o vetor de povos
            if(grafo[povoi][j]!=0 && vetor[j].visitado!=-1 && w>= vetor[j].peso && grafo[povoi][j]<=distanciaMAX){
                //se houver caminho entre os povos, se n�o tiver sido visitado, se o peso cabe na peso maximo e a dist�ncia for menor igual a dist�ncia m�xima
                //ser� alocado mais uma posi��o no vetor, o vetor vai receber o povo
                //e o i vai somar 
                vetor_adjacentes=realloc( vetor_adjacentes, (i +1) * sizeof(Povo) );
                vetor_adjacentes[i]=vetor[j];
                i++;
            }
        

    }
    int maior_adjastecente=-1;
    if(i==0){
        //se n�o encontrar nenhum adjascente a fun��o retorna -1
    	free(vetor_adjacentes);
    	return -1;
    }
    //maiorRaz�o vai retorna qual dos adjascentes tem a maior raz�o
    maior_adjastecente=maiorRazao(vetor_adjacentes,i);
    maior_adjastecente=vetor_adjacentes[maior_adjastecente].povo - 1;
    free(vetor_adjacentes);
    return maior_adjastecente;
    
}
double tempo(){// fun��o retorna tempo daquele momento desde 1 de janeiro de 1970
    struct timeval tv;
    gettimeofday(&tv,NULL);
    double micro = (double)(tv.tv_sec)+(double) (tv.tv_usec)/1000000.00;//Utilizando essa f�rmula se obtem o tempo em microsegundos
    return micro;
}


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
    //int t=1;
    //teste *int = (int *) calloc (1, sizeof(valores));
    //printf("ak\n");
    for(int i = 0; i<=capacidade; i++){
        for(int j = 0; j<qtdItens; j++){
            //printf("%d,%d\n",i,j);
            if(povos[j].peso <= i){
                if(resultados[i].valor < (resultados[i-povos[j].peso].valor + povos[j].habilidade)){
                    resultados[i].valor = resultados[i-povos[j].peso].valor + povos[j].habilidade;
                    //t++;
                    for(int k=0; k<qtdItens; k++){
                        resultados[i].qtd[k] = resultados[i-povos[j].peso].qtd[k];
                    }
                    //resultados[i].qtd = resultados[i-povos[j].peso].qtd;
                    resultados[i].qtd[j]=resultados[i].qtd[j]+1;
                }
            }
        }
    }

    return resultados;
}