#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no*esq;
    struct no*dir;
};

int vazia(struct no*r){
    return (r == NULL);
}

//retorna a quantidade de chaves na arvore
int conta_chaves(struct no*r){
    if(!vazia(r)){
        return 1 + conta_chaves(r->esq) + conta_chaves(r->dir);
    }else 
        return 0;
}

//imprime a ordem crescente as chaves na arvore qu estao no intervalo fechado [a,b]
//pre-condicao: a <= b
//nao percorre as subarvores desnecessarias
void imprime_intervalo(struct no* r, int a, int b){
    if(!vazia(r)){
        if(r->info > a){  imprime_intervalo(r->esq, a, b); }
        if(r->info >= a && r->info <= b){
            printf("%d ", r->info);
        }
        if(r->info < b){  imprime_intervalo(r->dir, a, b); }
    }
}

//retorna a chave seguinte ao valor x, isto e, a menor chave maior que x
//entrada: arvore r e valor x
int chave_seguinte(struct no* r, int x){
    if(!vazia(r)){
        if(r->info > x){
            int aux = chave_seguinte(r->esq, x);
            if(aux == -1) return r->info;
            else return aux;
        }else{
            return chave_seguinte(r->dir, x);
        }
    }else return -1;
}

//retorna a soma dos valores da arvore
int somar(struct no* r){
    if(!vazia(r)){
        return r->info + somar(r->esq) + somar(r->dir);
    }else return 0;
}

/*
struct no{
    int info;
    struct no*prox;
};

int vazia(struct no* l){
    return (l == NULL);
}

//retorna o numero de elementos da lista
int conta_elementos(struct no* l){
    if(!vazia(l)){
        return 1 + conta_elementos(l->prox);
    }else return 0;
}

//retorna a lista apos o n primeiros elementos, modificando a lista original
struct no* lista_aposN(struct no* l, int n){
    if(!vazia(l) || n == 0)
        return NULL;
    if(n == 1){
        Lista* aux = l->prox;
        l->prox = NULL;
        return aux;
    }
    else return lista_aposN(l->prox, n-1);
}

//faz a intercalaçõa de 2 listas ordenadas, retornando a cabeça da lista resultante
//pre-condicao: nenhuma
//pos-condicao: listas sao intercaladas de maneira ordenada, gerando uma unica lista
//alterar listas passadas como parametro, sem criar uma nova lista, isto e, nao deve haver alocaçao de memoria
struct no* merge_ord(struct no* l1, struct no* l2){
    if(vazia(l1)) return l2;
    if(vazia(l2)) return l1;
    struct no* aux = NULL;
    if(l1->info < l2->info){
        aux = l1;
        aux->prox = merge_ord(l1->prox, l2);
    }else{
        aux = l2;
        aux->prox = merge_ord(l1, l2->prox);
    }
    return aux;
}

//implementa o algoritmo mergesort para lista encadeada
struct no* l mergesort(struct no* l){
    if(vazia(l))
        return NULL;
    int tam = tamanho(l);
    
    if(tam >= 2){
        struct no* l2= lista_aposN(l, (int)(tam/2));
        struct no* l1 = mergesort(l);
        l2 = mergesort(l2);
        return merge_ord(l1, l2);
    }else
        return l;
}

*/


int main(){

}