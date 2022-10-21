#include "tp.h"
void lerArquivo(char *nomeArq,char *nomeSaida){
    //Abre o arquivo de texto
    long long int *lista= NULL;
    lista=crivoEratostenes();
    FILE *arq = fopen(nomeArq, "r");
    if(arq == NULL) printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
    char linha[15];
    //ListaR é a lista resultante,ou seja irá guardar os valores resultantes 
    long long int *listaR=NULL;
    //Aloca espaço para o primeiro resultado
    listaR=(long long int*)malloc(sizeof(long long int));
    long long int n;
    int i = 0;   
    //Enquanto não encontrar o final do arquivo a varivel linha recebe uma linha do arquivo que é correspondente a um número
    while(!feof(arq)){
        fgets(linha,15,arq);
        //n recebe o numero convertido em long int
        n=atol(linha);
        //A função fatorar retorna a quantidade de números primos diferentes que divide n
        n=qtdPrimos(n,lista);
        //A função calcXulambs retorna as combinações possiveis com  quantidade de n-números 
        n=calcXulambs(n);
        //A listar recebe o resultado final
        listaR[i]=n;
        //listaTempos[i]=tr;
        i++;
        //É alocado espaço para o próximo resultado
        listaR = realloc( listaR, (i +1) * sizeof(long long int) );
    }
     //Envia a lista resultante para ser gravada em um arquivo 
    escreverArquivo(nomeSaida,listaR,i);
    //Desaloca a listaR
    free(listaR);
    //Fecha o arquivo 
    fclose(arq);
}

long long int calcXulambs (long long int n){//função que calcula o número total de Xulambs e o retorna
    //n é o número de primos diferentes presentes em fatoração de um número determinado, fornecido pela função fatorar
    if(n<2){
        return 0; // caso n seja menor que dois sabemos que não há nenhum Xulambs, por isso o retorno é 0
    }
    if(n==2){
        return 1; // caso n seja igual a dois sabemos que há somente um Xulambs, por isso o retorno é 1
    }
    // se chegou nesse ponto já sabemos que há mais de um Xulambs, independente do valor n
    long long int nXulambs = 1;// nXulambs é a variável de retorno da função. Ele recebe o valor 1 inicialmente, devido a combinação de todos os números juntos.
    // O laço a seguir vai começar a somar as combinações dos n elementos tomados de i em i (sendo que i inicia com o valor de n-1 e diminui 1 a cada volta) 
    // até que i seja =2, conforme a fórmula de análise combinatória, dada por: n!/i!(n-i)!
    for(long long int i = n-1; i>=2; i--){
        nXulambs = nXulambs + (fatorial(n)/(fatorial(i)*fatorial(n-i)));
    }
    return nXulambs;
}

long long int fatorial (long long int n){//função que retorna a fatorial 
    long long int resultado = 1; // resultado começa em 1 porque um número multiplicado por 1 é ele mesmo
    for (long long int i=n; i>1; i--){// o laço começa de n e vai diminuindo até que i seja maior que 1, fatorial de 1 é 1, então não altera o resultado
        resultado = resultado * i;//resultado multiplica ele mesmo por i
    }
    return resultado;
}

void escreverArquivo(char *nomeSaida,long long int *listaR,int i){
    //Abre o arquivo de texto
    FILE *arq = fopen(nomeSaida, "w");
    if(arq == NULL) printf("\nERRO NA ABERTURA DO ARQUIVO\n\n\n");
    char linha[15]; 
    //Percorre o vetor recebido, a cada posição do vetor é escrito uma linha no arquivo
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

long long int* crivoEratostenes(){//essa função retorna uma lista com todos os índices de números primos com valor 0 e o restante com 1
    long long int *lista= NULL;
    lista=(long long int*)calloc(1000000,sizeof(long long int));//espaço na memória alocaco com calloc, porque essa função preenche todas as posições com 0 logo na criação
    for (long long int i=2; i<1000; i++) {//pela lógica do crivo é necessário percorrer o vetor somente até a raiz do maior número da lista
        if (lista[i]==0) {//as posições da lista que estão com valor 0 tem índice de número primo, então todas as posições com índice de números múltiplos desse índice serão preenchidas com valor 1
            for (long long int j=i+i; j<1000000; j+=i) {
                lista[j]=1; // removendo da lista
            }         
        }
    }
    return lista;
}

long long int qtdPrimos(long long int n,long long int* lista){//recebe o número a ser fatorado e a lista de números primos
    long long int nPrimos=0, j=0;// declaração da variável que vai contar o número de primos diferentes presentes e a de teste pra saber se é a primeira vez que o número será analisado como divisor
    float raiz;   
    raiz=sqrt(n);
    raiz=ceil(raiz);//variável raiz recebe a raiz do número a ser fatorado. Função ceil serve pra arrendondar um número pra cima
    long long int x=n;//x recebe o valor de n para serem feitas operações  
    for (long long int i=2; i<=raiz;) {//a lista será percorrida da posição 2 até a raiz de n, seguindo a lógica do crivo
        if(lista[i]==0 && x%i==0){//se o índice da lista for um número primo (com valor 0) e for divisor de x, x vai receber sua divisão pelo índice
            x=x/i;
            if(j!=i){//se a variável j for diferente do índice significa que é primeira vez que esse número é analisado, então a variável nPrimos aumenta em 1
                nPrimos++;
            }
            j=i;// depois da divisão j recebe o índice
        }else{
            i++;// caso x não seja divisível por i, i aumenta em 1 para que o próximo índice seja analisado.
        }
    }
    if(x!=1){// o método do crivo garante que se chegou na raiz do número fatorado e a fatoração não está completa, existem dois casos:
    //se já existir pelo menos um divisor primo, então só existe mais um divisor primo possível; se não existir nenhum primo divisor até a raiz, então o número fatorado é primo
        nPrimos++;//nos dois casos basta adicionar 1 no número de primos
    }
    return nPrimos;
}

 double tempo(){// função retorna tempo daquele momento desde 1 de janeiro de 1970
    struct timeval tv;
    gettimeofday(&tv,NULL);
    double micro = (double)(tv.tv_sec)+(double) (tv.tv_usec)/1000000.00;//Utilizando essa fórmula se obtem o tempo em microsegundos
    return micro;
}