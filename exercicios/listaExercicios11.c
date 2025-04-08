#include <stdio.h>
#include <stdlib.h>

//esquema R-way
#define TAM_ALFABETO 26
#define ASCII_BASE 97 //codigo da letra A

typedef struct no{
    struct no* filho[TAM_ALFABETO];
    int valor;
} noTRIE;

typedef noTRIE *TRIE;

typedef struct {
    TRIE raiz;
} arvoreTRIE;


TRIE criarNo(){
    TRIE aux = (TRIE) malloc (sizeof(noTRIE));
    aux->valor = -1;

    for(int i =0; i < TAM_ALFABETO; i++)
        aux->filho[i] = NULL;
    return aux;
}

arvoreTRIE* criarArvore(){
    arvoreTRIE *aux = (arvoreTRIE*) malloc(sizeof(arvoreTRIE));
    aux->raiz = criarNo();
    return aux;
}


void inserir(arvoreTRIE* r, char* str, int valor){
    if(r->raiz == NULL) 
        r->raiz = criarNo();

    TRIE aux = r->raiz;

    while(*str){
        int index = *str - ASCII_BASE;
        
         if(aux->filho[index] == NULL){
            aux->filho[index] = criarNo();
         }
            aux = aux->filho[index];
            str++;
    }
    aux->valor = valor;
}



int buscar(arvoreTRIE* r, char *str){
    TRIE aux = r->raiz;
    while(*str){
        if(aux ==NULL)
            return -1;
        aux = aux->filho[*str - ASCII_BASE];
        str++;
    }
    return (aux != NULL) ? aux->valor : -1;
}


int temFilho(TRIE r){
    for(int i = 0; i< TAM_ALFABETO; i++)
        if(r->filho[i] != NULL)
            return 1;
    return 0;
}


void removerAux(TRIE* r, char* str){
    if(*r ==NULL) return;

    if(*str){
      removerAux(&(*r)->filho[*str - ASCII_BASE], str + 1);
    }
    
    if(*str == '\0' || (!temFilho(*r) && (*r)->valor == -1)){
        free(*r);
        *r = NULL;
    }else{
       (*r)->valor = -1;
    }   
}


void remover(arvoreTRIE* r, char* str){
    removerAux(&r->raiz, str);
}


void imprimirDicionarioAUX(TRIE r, char *str, int nivel){ //imprimir todas as chaves presentes na TRIE em ordem lexicografica
    if(r != NULL){
        if(r->valor != -1){
            str[nivel]= '\0';
            printf("%s  %d\n", str, r->valor);
        }
        for(int i = 0; i<TAM_ALFABETO; i++){
            if(r->filho[i] != NULL){
                str[nivel] = ASCII_BASE + i;
                imprimirDicionarioAUX(r->filho[i], str, nivel+1);
            }
        }
    }
}

void imprimirDicionario(arvoreTRIE* r){
    char str[50];
    imprimirDicionarioAUX(r->raiz, str, 0);
}



int main(){
arvoreTRIE * arvore = criarArvore();

inserir(arvore, "pai", 22);
inserir(arvore, "casa", 7);
inserir(arvore, "roma", 70);
inserir(arvore, "pato", 8);
inserir(arvore, "casca", 11);
inserir(arvore, "romano", 5);
inserir(arvore, "romance", 53);
inserir(arvore, "romenia", 33);

imprimirDicionario(arvore);
printf("\n");
printf("\n");
printf("\n");


//printf("string = %d\n", buscar(arvore, "pais"));

remover(arvore, "teto");
remover(arvore, "pata");
remover(arvore, "riso");

printf("string = %d\n", buscar(arvore, "pata"));


imprimirDicionario(arvore);
printf("\n");

char* str = "melo";

while(*str){
    printf("%d - ", *str);
    str++;
}

    return 0;
}