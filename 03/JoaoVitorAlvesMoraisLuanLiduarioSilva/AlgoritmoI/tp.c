#include "tp.h"
//Arquivo de operações em arquivos
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
    
    int v,i =0,k=0,vi=0,vj=0;  //Número de vértices
    fgets(linha,50,arq);
    v=atoi(linha);
    //int tam= v;
    printf("%d\n",v);
    strcpy(linha, "");
    int **grafo;
    grafo=alocar_matriz(v);
    ContAresta *vetorArestas;
    vetorArestas = (ContAresta *) calloc (v, sizeof(ContAresta *));
    vetorArestas=preecher(vetorArestas,v);
    //váriveis utilizadas em cada instancia 
    int aux=0;
   while(!feof(arq)){
        c=getc(arq);
        linha[i]=c;
        i++;
        if(c==' ' || c=='\n' || feof(arq)){
            linha[i] = '\0';
            aux= atoi(linha);
            strcpy(linha, ""); 
            c='y';
            i=0;
            if(k==0){
                vi = aux;
                //printf("%d-",vi );
                k=1;
            }else if(k==1){
                vj = aux;
                vetorArestas[vi].naresta=vetorArestas[vi].naresta+1;
                vetorArestas[vj].naresta=vetorArestas[vj].naresta+1;
                grafo=insereAresta(vi,vj,grafo);
                //printf("%d\n",vj );
                k=0;
                //printf("%d-%d\n",vi,vj ); 
            }

        }       
   }
   heapsortVetorContAresta(vetorArestas,v);
   // for(int h=0;h<v;h++){
   //  printf("Vetor arestas [%d]=%d\n",vetorArestas[h].vertice,vetorArestas[h].naresta);
   // }
    //printMatriz(tam,grafo);
    forca_brutaII(grafo,v);
    //guloso(vetorArestas,tam,grafo);
    //gulosoII(vetorArestas,v,grafo);
    
    //Fecha os arquivos
    free(vetorArestas);
    grafo=liberar_matriz(v,grafo);
    fclose(arq);
    fclose(arqSaida);

}
void escreverArquivo(int *caminho,int i,FILE *arqSaida){
    //Abre o arquivo de texto
    if(arqSaida == NULL) printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
    char linha[100]; 
    //Percorre o vetor recebido, a cada posição do vetor é escrito na linha no arquivo
    for(int j=0;j<i;j++){
        fprintf(arqSaida, "%d",caminho[j]);
        fprintf(arqSaida, "%s"," ");
        
    }
    fprintf(arqSaida, "%s","\n");
}
double tempo(){// função retorna tempo daquele momento desde 1 de janeiro de 1970
    struct timeval tv;
    gettimeofday(&tv,NULL);
    double micro = (double)(tv.tv_sec)+(double) (tv.tv_usec)/1000000.00;//Utilizando essa fórmula se obtem o tempo em microsegundos
    return micro;
}
//Grafos
int ** insereAresta(int povoi,int povoj,int **grafo){
    //Atribui a distância na matriz
    grafo[povoi][povoj]=1;
    grafo[povoj][povoi]=1;
    return grafo;
}

int **alocar_matriz(int vertices){
  int **matriz;  /* ponteiro para a matriz */
  /* aloca as linhas da matriz */
  matriz = (int **) calloc (vertices, sizeof(int *));   // Um vetor de vertices ponteiros para int
  /* aloca as colunas da matriz */
  for ( int i = 0; i < vertices; i++ ) {
      matriz[i] = (int*) calloc (vertices, sizeof(int));    /* vertices vetores de int */
      }
  return (matriz); /* retorna o ponteiro para a matriz */
}
int **liberar_matriz (int vertices, int **matriz){
  if (matriz == NULL) return (NULL);
  for (int i=0; i<vertices; i++) free (matriz[i]); /* libera as linhas da matriz */
  free (matriz);      /* libera a matriz (vetor de ponteiros) */
  return (NULL); /* retorna um ponteiro nulo */
}

//forca_bruta
void forca_bruta(int **grafo,int n){
    int x=0,tamanhoAux;
    int *aux;
    int mcvi=-1;
    int testes =0;
    for(int i=0;i<n;i++){
        //aux=NULL;
        aux=(int*) malloc(sizeof(int)*n);
        aux[0]=i;
        tamanhoAux=1;
        for(int j=i+1;j<n;j++){
            //printf("J:%d\n",j );
            x=0;
            x=verifica(j,grafo,aux,tamanhoAux,tamanhoAux);
            testes++;
            // while(x<tamanhoAux && x!=-1){
            //     testes++;
            //     if(grafo[j][aux[x]]==1){
            //         x=-1;
            //     }else{
            //          x++;
            //     }
            // }
            if(x!=-1){
                aux[tamanhoAux]=j;
                tamanhoAux++;
            }
        }
        //printf("BLA\n");
        if(tamanhoAux>mcvi){
            mcvi=tamanhoAux;
        }
        free(aux);
        //printVetor(tamanhoAux,aux);
    }
    printf("CVI: %d fez op : %d\n",mcvi,testes);
}

//testes print
void printMatriz(int v,int **grafo){
    for (int i=0; i<v; i++ ){
        for (int j=0; j<v; j++ ){
    
         printf ("matriz[%d][%d] = %d\n",i,j, grafo[ i ][ j ]);
        }
    }
}
void printVetor(int v,int *vetor){
    for (int i=0; i<v; i++ ){   
         printf ("vetor[%d]= %d\n",i,vetor[ i ]);
    }
}
//Guloso I
void guloso(ContAresta *vetorArestas,int nvertices,int **grafo){
    int * cvi;
    cvi=(int*) malloc(sizeof(int)*nvertices);
    int tam=1,aux=1;
    cvi[0]=vetorArestas[0].vertice;
    int testes = 0;
    for(int i = 1; i < nvertices; i++){
        if(vetorArestas[i].naresta==0){
            cvi[tam]=vetorArestas[i].vertice;
            tam++;
        }else{
            aux=verifica(vetorArestas[i].vertice,grafo,cvi,tam,vetorArestas[i].naresta);
            if(aux==0){
                cvi[tam]=vetorArestas[i].vertice;
                tam++;
            }
        }
        testes++;
    }
    free(cvi);
    printf("Tamanho %d- com %d\n",tam,testes );
}
ContAresta* preecher(ContAresta* vetor,int nvertices){
    for(int i=0;i<nvertices;i++){
        vetor[i].vertice=i;
        vetor[i].naresta=0;
    }
    return vetor;
}
//heapsort
void refazerVetorContAresta(int esq, int dir, ContAresta *a,long int *comparacao,long int * mov) {
//refaz a heap garantindo que o pai seja maior que o dois filhos
    int i = esq;
    int j;
    ContAresta x;
    j = i * 2;
    x = a[i];
    (*mov)++;
    while (j <= dir) {
        if (j < dir) {
            if (a[j].naresta < a[j+1].naresta){
                  (*comparacao)++;
                  j++;
            }
        }
        if (x.naresta >= a[j].naresta){
            (*comparacao)++;
            break;
        }
        a[i] = a[j];
        (*mov)++;
        i = j;
        j = i * 2;
    }
    a[i] = x;
    (*mov)++;

}
void construirVetorContAresta(ContAresta * a, int n,long int * comparacao,long int *mov) {
    int esq;
    esq = n / 2 +1;
    while (esq >0) {
        esq--;
        refazerVetorContAresta(esq, n, a,comparacao,mov);
    }
}
void heapsortVetorContAresta(ContAresta *a, int n) {
    int esq, dir;
    long int mov=0,comparacao=0;
    ContAresta x;
    construirVetorContAresta(a, n-1,&comparacao,&mov); /* constroi o heap */
    esq = 0;
    dir = n-1;
    while (dir >= 1) {// pega o primeiro elemento coloca na ultima posicao (porque ele é o maior de todos) e chama a função para reconstrução da heap
    /* ordena o vetor */
        x = a[0];
        a[0] = a[dir];
        a[dir] = x;
        mov=mov+3;
        dir--;
        refazerVetorContAresta(esq, dir, a,&comparacao,&mov);
    }
    //printf("Comparacao : %ld\n",comparacao);
    //printf("Movimentacao : %ld\n",mov);
}

//verifica
int verifica(int v,int ** grafo,int * cvi, int tamCvi, int qtdArestas){
   // int x=0;
    int i=0;
    while(i<tamCvi && i<=qtdArestas){
       if(grafo[v][cvi[i]]==1 ){
            //printf("%d ndeopverifica\n",i);
            return -1; // existe aresta
        }
        i++; 
    }
    // for(int i = 0;i<tamCvi;i++){
    //     if(grafo[v][cvi[i]]==1 ){
    //         return -1; // existe aresta
    //     }
    // }
    //printf("%d ndeopverifica\n",i);
    return 0;
}

//GULOSO II

void gulosoII(ContAresta *vetorArestas,int nvertices,int **grafo){
    ContAresta * cvi;
    cvi=(ContAresta*) malloc(sizeof(ContAresta)*nvertices);
    int tam= nvertices;
    cvi=vetorArestas;
    for(int i = 0; i < nvertices; i++){
        if(vetorArestas[i].naresta!=-1){
            //printf("verticeI= %d e narestaI %d\n",cvi[i].vertice,cvi[i].naresta);
            cvi = retirarAd(i,vetorArestas,&tam,grafo,nvertices);
            for(int h=0;h<nvertices;h++){
                //printf("Vetor arestas [%d]=%d\n",cvi[h].vertice,cvi[h].naresta);
            }
            //printf("\n\n\n");
        }
    }
    free(cvi);
    printf("Tamanho %d\n",tam);
}

ContAresta * retirarAd(int v,ContAresta *vetorArestas,int *tam,int ** grafo,int nvertices){
    int i = 0;
    int j = nvertices-1;
    // for(int h=0;h<5;h++){
    //             printf("Vetor arestas [%d]=%d\n",vetorArestas[h].vertice,vetorArestas[h].naresta);
    //         }
    //printf("entrou\n");
    while(i<vetorArestas[v].naresta){
        if(grafo[vetorArestas[v].vertice][vetorArestas[j].vertice]==1){
            // printf("red\n");
            i++;
            if(vetorArestas[j].naresta!=-1){
                vetorArestas[j].naresta=-1;
                (*tam)--;
            }
        }
        j--;    
    }
    // getchar();
    // for(int h=0;h<5;h++){
    //             printf("Vetor arestas [%d]=%d\n",vetorArestas[h].vertice,vetorArestas[h].naresta);
    //         }
    // getchar();
    return vetorArestas;
}
void forca_brutaII(int **grafo,int n){
   // n=4;
    //int aux = n;
    int  teste = 0, j=0;
    int * cvi;
    int * aux;
    cvi=(int*) malloc(sizeof(int)*n);
    while(j<n){
        cvi[j]=j;
        j++;
    }

    //printCombination(cvi, n, i);
    for(int i = n; i>1;i--){//i é o número de elementos presentes nos conjuntos
        //aux=cvi;
        aux=(int*) malloc(sizeof(int)*i);
        // int qtd;
        //qtd= calcXulambs(n,i);
        teste=verificaCombinacoes(cvi,aux,0,n-1,0,i,grafo);//arr, data, 0, n-1, 0, r,grafo
        //(int *arr, int n, int r,int **grafo)
        if(teste==1){
            printf("resultado %d\n",i);
            return;
        }
        free(aux);
        //printf("teste %d\n",teste);
    }
    printf("resultado 1\n");
}

// int calcXulambs (int n,int i){
    
//     int qtd=0;
//     qtd = (fatorial(n)/(fatorial(i)*fatorial(n-i)));

//     return qtd;
// }

// int fatorial (int n){//função que retorna a fatorial 
//     int resultado = 1; // resultado começa em 1 porque um número multiplicado por 1 é ele mesmo
//     for (int i=n; i>1; i--){// o laço começa de n e vai diminuindo até que i seja maior que 1, fatorial de 1 é 1, então não altera o resultado
//         resultado = resultado * i;//resultado multiplica ele mesmo por i
//     }
//     return resultado;
// }

int verificaCombinacoes(int *arr, int *data, int start, int end, int index, int r,int **grafo){
  // int i, j;
  int teste=0;

  if (index == r){
    
    for (int j=0; j<r; j++){
     // printf("%d ", data[j]);
      teste=verificarConjunto(data,r,grafo,data[j]);
      if(teste==-1){
        //printf("Estou ak %d\n",teste);
        return teste;
      }
    }
    //printf("teste %d",teste);
    //verificarConjunto(data,r,grafo);
    return 1;
  }
 
  for (int i=start; i<=end && end-i+1 >= r-index; i++){
    data[index] = arr[i];
    teste=verificaCombinacoes(arr, data, i+1, end, index+1, r,grafo);
    if(teste==1){
        return teste;
    }
    //return teste;
  }
  return teste;
  //return 0;
}

// int printCombination(int *arr, int n, int r,int **grafo)
// {
//   int data[r];
//   int teste=0;

//   teste=combinationUtil(arr, data, 0, n-1, 0, r,grafo);
//   //printf("TESTE: %d\n",teste);
//   return teste;
// }
 
// int main()
// {
//   int arr[] = {1, 2, 3, 4, 5};
//   int r = 3;
//  int n = sizeof(arr)/sizeof(arr[0]);
//   printCombination(arr, n, r);
// }

int verificarConjunto(int * cvi,int n,int **grafo,int v){
    //printf("ConjuntoC:\n");
        for(int i = 0; i<n;i++){
                if(grafo[cvi[i]][v]==1){
                    //printf("Existe aresta %d\n",v );
                    return -1;
                }
            //printf("%d ",cvi[i] );
        }

        return 1;
        //printf("\n");
}