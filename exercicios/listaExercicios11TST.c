#include <stdio.h>
#include <stdlib.h>

typedef struct noTST{
    char ch; //caracter da TRIE
    int valor; //valor associado a chave
    struct noTST * menor; //antes de ch na ordem lexicografica
    struct noTST* igual;
    struct noTST * maior; //depois de ch na ordem lexicogafica
} noTST_TRIE;

typedef noTST_TRIE* TRIE;

void inserirTST(TRIE * r, char * str, int valor){
    if(*str){
        if(*r == NULL){
            *r = (noTST_TRIE*) malloc(sizeof(noTST_TRIE));
            (*r)->ch = *str;
            (*r)->valor = -1;
            (*r)->igual = NULL;
            (*r)->menor = NULL;
            (*r)->maior = NULL;

            inserirTST(&(*r)->igual, str+1, valor);
            if(*(str+1) == '\0')
                (*r)->valor = valor;
        }
        else{
            if(*str < (*r)->ch)
                inserirTST(&(*r)->menor, str, valor);
            else
                if(*str > (*r)->ch)
                inserirTST(&(*r)->maior, str, valor);
                else{
                    inserirTST(&(*r)->igual, str+1, valor);
                    if(*(str+1) == '\0')
                        (*r)->valor =valor;
                }
        }
    }
}


void removerTST(TRIE * r, char * str){
    if(*str){
        if(*r != NULL){
            if(*str < (*r)->ch)
                removerTST(&(*r)->menor, str);
            else
                if(*str > (*r)->ch)
                    removerTST(&(*r)->maior, str);
                else
                    if((*r)->ch == *str){
                        if(*(str+1) == '\0' && (*r)->ch != -1)
                            (*r)->valor = -1;
                        else
                            removerTST(&(*r)->igual, str+1);
                    }
            if(((*r)->menor == NULL) && ((*r)->igual == NULL) && ((*r)->maior == NULL) && ((*r)->valor == -1)){
                free(*r);
                *r = NULL;
            }
        }
    }
}

void imprimirDicionarioAux(TRIE raiz, char *base, char *str){
    if(raiz != NULL){
        imprimirDicionarioAux(raiz->menor, base, str);
        *str = raiz->ch;
        if(raiz->valor != -1){
            *(str+1) = '\0';
            printf("%s\n", base);
        }
        imprimirDicionarioAux(raiz->igual, base, str+1);
        imprimirDicionarioAux(raiz->maior, base, str);
    }
}

void imprimir_dicionarioTST(TRIE *r){
    char str[50] = "\0";
    imprimirDicionarioAux(*r, str, str);
}


int buscarTST(TRIE *r, char *str) {
    if (*r == NULL)
        return -1;

    if (*str < (*r)->ch)
        return buscarTST(&((*r)->menor), str);
    else if (*str > (*r)->ch)
        return buscarTST(&((*r)->maior), str);
    else {
        if (*(str + 1))
            return buscarTST(&((*r)->igual), str + 1);
        else
            return (*r)->valor; // Retorna o valor associado à palavra
    }
}


char* prefixoMaisLongo(TRIE r, char* str) //retorna o prefixo mais longo da cadeia str que esta na TRIE
{
    static char prefixo[50]; // Armazena o prefixo mais longo encontrado
    int i = 0;
    while (r != NULL && *str) {
        if (*str < r->ch) {
            r = r->menor;
        } else if (*str > r->ch) {
            r = r->maior;
        } else { 
            prefixo[i++] = r->ch; // Adiciona ao prefixo encontrado
            if (r->valor != -1) {
                prefixo[i] = '\0'; // Marca o final do prefixo válido
            }
            r = r->igual;
            str++;
        }
    }
    
    if (i == 0) // Se nenhum prefixo válido foi encontrado
        return NULL;
    
    prefixo[i] = '\0'; // Garante que a string está bem formada
    return prefixo;
}


//conta palavras armazenadas a partir do nó t
int contaPalavras(TRIE t){
    if(t == NULL) return 0;
    int cont = 0;
    if(t->valor != -1){
        cont = 1;
    }
    //cont += contaPalavras(t->menor);
    //cont += contaPalavras(t->igual);
    //cont += contaPalavras(t->maior);
    //return cont;
    cont++;
    return contaPalavras(t->menor) + contaPalavras(t->igual) + contaPalavras(t->maior);
}





int main(){

    TRIE tst = NULL;

    inserirTST(&tst, "penta", 10);
    inserirTST(&tst, "lado", 2);
    inserirTST(&tst, "pata", 4);
    inserirTST(&tst, "geladeira", 1);
    inserirTST(&tst, "pelo", 7);
    inserirTST(&tst, "cabo", 33);
    inserirTST(&tst, "ar", 8);


    imprimir_dicionarioTST(&tst);
    printf("\n");


    /*
    char* resultado = prefixoMaisLongo(tst, "pentagrama");
    if (resultado)
        printf("Prefixo mais longo encontrado: %s\n", resultado);
    else
        printf("Nenhum prefixo encontrado.\n");
    */

    printf("Quantidade de palavras armazenadas: %d", contaPalavras(&tst));

    return 0;
}