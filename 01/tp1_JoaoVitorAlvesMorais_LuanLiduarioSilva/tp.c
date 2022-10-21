#include "tp.h"
void lerArquivo(char *nomeArq,char *nomeSaida){
    //Abre o arquivo de texto
    long long int *lista= NULL;
    lista=crivoEratostenes();
    FILE *arq = fopen(nomeArq, "r");
    if(arq == NULL) printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
    char linha[15];
    //ListaR � a lista resultante,ou seja ir� guardar os valores resultantes 
    long long int *listaR=NULL;
    //Aloca espa�o para o primeiro resultado
    listaR=(long long int*)malloc(sizeof(long long int));
    long long int n;
    int i = 0;   
    //Enquanto n�o encontrar o final do arquivo a varivel linha recebe uma linha do arquivo que � correspondente a um n�mero
    while(!feof(arq)){
        fgets(linha,15,arq);
        //n recebe o numero convertido em long int
        n=atol(linha);
        //A fun��o fatorar retorna a quantidade de n�meros primos diferentes que divide n
        n=qtdPrimos(n,lista);
        //A fun��o calcXulambs retorna as combina��es possiveis com  quantidade de n-n�meros 
        n=calcXulambs(n);
        //A listar recebe o resultado final
        listaR[i]=n;
        //listaTempos[i]=tr;
        i++;
        //� alocado espa�o para o pr�ximo resultado
        listaR = realloc( listaR, (i +1) * sizeof(long long int) );
    }
     //Envia a lista resultante para ser gravada em um arquivo 
    escreverArquivo(nomeSaida,listaR,i);
    //Desaloca a listaR
    free(listaR);
    //Fecha o arquivo 
    fclose(arq);
}

long long int calcXulambs (long long int n){//fun��o que calcula o n�mero total de Xulambs e o retorna
    //n � o n�mero de primos diferentes presentes em fatora��o de um n�mero determinado, fornecido pela fun��o fatorar
    if(n<2){
        return 0; // caso n seja menor que dois sabemos que n�o h� nenhum Xulambs, por isso o retorno � 0
    }
    if(n==2){
        return 1; // caso n seja igual a dois sabemos que h� somente um Xulambs, por isso o retorno � 1
    }
    // se chegou nesse ponto j� sabemos que h� mais de um Xulambs, independente do valor n
    long long int nXulambs = 1;// nXulambs � a vari�vel de retorno da fun��o. Ele recebe o valor 1 inicialmente, devido a combina��o de todos os n�meros juntos.
    // O la�o a seguir vai come�ar a somar as combina��es dos n elementos tomados de i em i (sendo que i inicia com o valor de n-1 e diminui 1 a cada volta) 
    // at� que i seja =2, conforme a f�rmula de an�lise combinat�ria, dada por: n!/i!(n-i)!
    for(long long int i = n-1; i>=2; i--){
        nXulambs = nXulambs + (fatorial(n)/(fatorial(i)*fatorial(n-i)));
    }
    return nXulambs;
}

long long int fatorial (long long int n){//fun��o que retorna a fatorial 
    long long int resultado = 1; // resultado come�a em 1 porque um n�mero multiplicado por 1 � ele mesmo
    for (long long int i=n; i>1; i--){// o la�o come�a de n e vai diminuindo at� que i seja maior que 1, fatorial de 1 � 1, ent�o n�o altera o resultado
        resultado = resultado * i;//resultado multiplica ele mesmo por i
    }
    return resultado;
}

void escreverArquivo(char *nomeSaida,long long int *listaR,int i){
    //Abre o arquivo de texto
    FILE *arq = fopen(nomeSaida, "w");
    if(arq == NULL) printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
    char linha[15]; 
    //Percorre o vetor recebido, a cada posi��o do vetor � escrito uma linha no arquivo
    for(int j=0;j<i;j++){
        //printf("lista r %d:%lld\n",j,listaR[j] );
        sprintf(linha, "%lld",listaR[j]);
        strcat(linha, "\n"); //adiciona string 1 no final da string 2
        fputs(linha,arq);
        strcpy(linha, "");//Limpa a string
    }
    //Fecha o arquivo
    fclose(arq);
}

long long int* crivoEratostenes(){//essa fun��o retorna uma lista com todos os �ndices de n�meros primos com valor 0 e o restante com 1
    long long int *lista= NULL;
    lista=(long long int*)calloc(1000000,sizeof(long long int));//espa�o na mem�ria alocaco com calloc, porque essa fun��o preenche todas as posi��es com 0 logo na cria��o
    for (long long int i=2; i<1000; i++) {//pela l�gica do crivo � necess�rio percorrer o vetor somente at� a raiz do maior n�mero da lista
        if (lista[i]==0) {//as posi��es da lista que est�o com valor 0 tem �ndice de n�mero primo, ent�o todas as posi��es com �ndice de n�meros m�ltiplos desse �ndice ser�o preenchidas com valor 1
            for (long long int j=i+i; j<1000000; j+=i) {
                lista[j]=1; // removendo da lista
            }         
        }
    }
    return lista;
}

long long int qtdPrimos(long long int n,long long int* lista){//recebe o n�mero a ser fatorado e a lista de n�meros primos
    long long int nPrimos=0, j=0;// declara��o da vari�vel que vai contar o n�mero de primos diferentes presentes e a de teste pra saber se � a primeira vez que o n�mero ser� analisado como divisor
    float raiz;   
    raiz=sqrt(n);
    raiz=ceil(raiz);//vari�vel raiz recebe a raiz do n�mero a ser fatorado. Fun��o ceil serve pra arrendondar um n�mero pra cima
    long long int x=n;//x recebe o valor de n para serem feitas opera��es  
    for (long long int i=2; i<=raiz;) {//a lista ser� percorrida da posi��o 2 at� a raiz de n, seguindo a l�gica do crivo
        if(lista[i]==0 && x%i==0){//se o �ndice da lista for um n�mero primo (com valor 0) e for divisor de x, x vai receber sua divis�o pelo �ndice
            x=x/i;
            if(j!=i){//se a vari�vel j for diferente do �ndice significa que � primeira vez que esse n�mero � analisado, ent�o a vari�vel nPrimos aumenta em 1
                nPrimos++;
            }
            j=i;// depois da divis�o j recebe o �ndice
        }else{
            i++;// caso x n�o seja divis�vel por i, i aumenta em 1 para que o pr�ximo �ndice seja analisado.
        }
    }
    if(x!=1){// o m�todo do crivo garante que se chegou na raiz do n�mero fatorado e a fatora��o n�o est� completa, existem dois casos:
    //se j� existir pelo menos um divisor primo, ent�o s� existe mais um divisor primo poss�vel; se n�o existir nenhum primo divisor at� a raiz, ent�o o n�mero fatorado � primo
        nPrimos++;//nos dois casos basta adicionar 1 no n�mero de primos
    }
    return nPrimos;
}

 double tempo(){// fun��o retorna tempo daquele momento desde 1 de janeiro de 1970
    struct timeval tv;
    gettimeofday(&tv,NULL);
    double micro = (double)(tv.tv_sec)+(double) (tv.tv_usec)/1000000.00;//Utilizando essa f�rmula se obtem o tempo em microsegundos
    return micro;
}