#include <stdio.h>
#include <stdlib.h>

#define TAM_ALFABETO 26
#define ASCII_BASE 97 //codigo da letra A

//essa implementacao pressupoe chaves formadas por letras minusculas do alfabeto de a..z
typedef struct no{
    struct no* filho[TAM_ALFABETO];
    int valor; //valor associado a chave. 0 se a chave nao existe
    int n; //quantidade de filhos nao-nulos para facilitar a remoção
} noTRIE;

typedef noTRIE *TRIE;

//imprime todas as palavras armazenadas na trie em ordem alfabetica e o seu respectivo valor
void imprimir_dicionario(TRIE r); //tenho na lista




int main(){

}