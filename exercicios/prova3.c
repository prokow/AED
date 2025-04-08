#include <stdio.h>
#include <stdlib.h>

#define ORDEM 5


/*
typedef struct nodeBMais{
    int chave[ORDEM-1];
    void * ponteiro[ORDEM];
    int eh_folha; //1 se for folha, 0 se for nó interno
    int numChaves; //numero de chaves armazenadas
} noBMais;

typedef noBMais* arvoreBMais;

//retorna o no-folha que contem info e sua posição no nó caso esteja na arvore B+
//ou NULL se info não esta em nó-folha
//e evita percorrer nós desnecessarios
arvoreBMais busca(arvoreBMais r, int info, int *pos){
    if(r == NULL) return NULL;
    if(r->eh_folha == 1){
        for(int i = 0; i < r->numChaves; i++){
            if(r->chave[i] == info){
                *pos = i;
                return r;
            }
        }
        return NULL;
    }else{
        for(int i = 0; i < r->numChaves; i++){
            if(info < r->chave[i]){
                return busca(r->ponteiro[i], info, pos);
            }
        }
        return busca(r->ponteiro[r->numChaves], info, pos);
    }
}

//imprime as chaves dentro do intervalo [a,b] que estao nas folhas
//pre-condicao: a <= b
//que nao percorra nós desnecessarios
void imprimeFolhasIntervalos(arvoreBMais r, int a, int b){
    if(r == NULL) return;
    if(r->eh_folha == 1){
        for(int i = 0; i < r->numChaves; i++){
            if(r->chave[i] >= a && r->chave[i] <= b){
                printf("%d ", r->chave[i]);
            }
        }
    }else{
        for(int i = 0; i < r->numChaves; i++){
            imprimeFolhasIntervalos(r->ponteiro[i], a, b);
        }
        imprimeFolhasIntervalos(r->ponteiro[r->numChaves], a, b);
    }
}


*/

struct no{
    int numChaves;
    int chave[ORDEM];
    struct no* filho[ORDEM + 1];
};
typedef struct no* arvoreB;


int isFolha(arvoreB r){
    return (r->filho[0] == NULL);
}

//retorna o numero de folhas da arvore
int contar_folhas(arvoreB r){
    if(r == NULL) return 0;

    int conta = 0;
    if(isFolha(r)) conta = 1;

    for(int i = 0; i <= r->numChaves; i++){
        conta += contar_folhas(r->filho[i]);
    }
    return conta;
}

//imprime as chaves no intervalo fechado[a,b], sem percorrer nós desnecessarios
void imprimir_intervalo(arvoreB r, int a, int b){
}


//retorna a chave seguinte ao valor de referencia ou -1 caso nao exista chave maior
//nao percorra nos desnecessarios
int proximaChave(arvoreB r, int valor_ref){

}

struct noLista{
    int info;
    struct noLista* prox;
};

//insere na cabeça da lista encadeada
struct noLista* insereLista(struct noLista* l, int info){
    struct noLista *aux = (struct noLista *)malloc(sizeof(struct noLista));
    aux->info = info;
    aux->prox = l;
    return aux;
}

//gera uma lista encadeada ordenada com as chaves da arvore B
struct noLista* arvoreB_to_Lista(arvoreB r){

}



int main() {
    printf("Hello, World!\n");
    return 0;
}


/*
struct no23{
    int chave_esq;
    int chave_dir;
    struct no23* esq;
    struct no23* meio;
    struct no23* dir;
    int n;
};

//conta o numero de nos cheios
int contaNosCheios(struct no23* r){
    if(r == NULL) return 0;
    if(r->n == 2) return 1 + contaNosCheios(r->esq) + contaNosCheios(r->meio) + contaNosCheios(r->dir);
    return contaNosCheios(r->esq) + contaNosCheios(r->meio) + contaNosCheios(r->dir);
}



*/


