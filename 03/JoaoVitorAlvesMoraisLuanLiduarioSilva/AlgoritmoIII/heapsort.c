#include "tp.h"
//heapsort
void refazerVetorContAresta(int esq, int dir, ContAresta * a) {
//refaz a heap garantindo que o pai seja maior que o dois filhos
    int i = esq;
    int j;
    ContAresta x;
    j = i * 2;
    x = a[i];   
    while (j <= dir) {
        if (j < dir) {
            if (a[j].naresta < a[j+1].naresta){           
                  j++;
            }
        }
        if (x.naresta >= a[j].naresta){
            break;
        }
        a[i] = a[j];  
        i = j;
        j = i * 2;
    }
    a[i] = x;
}
void construirVetorContAresta(ContAresta * a, int n) {
    int esq;
    esq = n / 2 + 1;
    while (esq >0) {
        esq--;
        refazerVetorContAresta(esq, n, a);
    }
}
void heapsortVetorContAresta(ContAresta *a, int n) {
    int esq, dir;
    ContAresta x;
    construirVetorContAresta(a, n-1); /* constroi o heap */
    esq = 0;
    dir = n-1;
    while (dir >= 1) {// pega o primeiro elemento coloca na ultima posicao (porque ele é o maior de todos) e chama a função para reconstrução da heap
    /* ordena o vetor */
        x = a[0];
        a[0] = a[dir];
        a[dir] = x;
        dir--;
        refazerVetorContAresta(esq, dir, a);
    }
}