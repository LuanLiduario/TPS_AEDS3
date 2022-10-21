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
    int n;  //Numero de instancias
    fgets(linha,50,arq);
    n=atoi(linha);
    //Leio Quantidade de instancias
    strcpy(linha, "");
    //váriveis utilizadas em cada instancia 
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