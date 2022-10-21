#include "tp.h"
//Arquivo de operações em arquivos
void lerArquivo(char *nomeArq,char *nomeSaida){
    //Abre o arquivo de texto
    FILE *arq = fopen(nomeArq, "r");
    if(arq == NULL){ 
        printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
        return;
    };
    char c;
    char linha[50];  
    int v,i =0,k=0,vi=0,vj=0;  
    fgets(linha,50,arq);
    v=atoi(linha);//v recebe a primeira linha do arquivo, que equivale a quantidade de vértices
    strcpy(linha, "");
    int **grafo;
    grafo=alocar_matriz(v);//chama uma função que aloca um matriz v x v
    int aux=0;
    while(!feof(arq)){//percorre o arquivo
        c=getc(arq);// recebe um caracter do arquivo
        linha[i]=c;//recebe todos os caracteres
        i++;
        if(c==' ' || c=='\n' || feof(arq)){//caso o caracter recebido encontrar espaço ou \n significa que a acabou a leitura de um número de vértice
            linha[i] = '\0';
            aux= atoi(linha);//aux coverte linha em inteiro
            strcpy(linha, ""); // zero as variveis responsaveis por fazer a leitura
            c='y';
            i=0;
            if(k==0){
                //se k for igual a 0 signfica que é o primeiro vertice da linha
                vi = aux;
                k=1;
            }else if(k==1){
                //se k for igual a 1 signfica que é o segundo vertice da linha
                vj = aux;
                //quando os dois vertices da linha são encontrados é chamado a função insereAresta para inserir a aresta entre eles
                grafo=insereAresta(vi,vj,grafo);
                //k recebe zero para a próxima linha
                k=0;
            }

        }       
    }
    //aux recebe o valor encontrado na solução foca_brutaII
    aux=forca_brutaII(grafo,v);
    //aux é escrito em arquivo utilizando a função escrever arquivo
    escreverArquivo(aux,nomeSaida);
    //libera a matriz da mémoria
    grafo=liberar_matriz(v,grafo);
    //fecha o arquivo
    fclose(arq);

}
void escreverArquivo(int resultado,char *nomeSaida){
    //Abre o arquivo de texto
    FILE *arqSaida = fopen(nomeSaida, "w");
    if(arqSaida == NULL) printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
    //escreve resultado no arquivo
    fprintf(arqSaida, "%d",resultado);
    //fecha o arquivo
    fclose(arqSaida);
}
double tempo(){// função retorna tempo daquele momento desde 1 de janeiro de 1970
    struct timeval tv;
    gettimeofday(&tv,NULL);
    double micro = (double)(tv.tv_sec)+(double) (tv.tv_usec)/1000000.00;//Utilizando essa fórmula se obtem o tempo em microsegundos
    return micro;
}