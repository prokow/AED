#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int info;
    struct no* prox;
}Lista;

/*
lista duplamente encadeada
typedef int TipoItem; // tipo dos elementos na lista

typedef struct no { //estrutura para lista duplamente encadeada
    TipoItem info;
    struct no * ant; // ponteiro para o elemento anterior
    struct no * prox; // ponteiro para pr´oximo elemento
} Lista; 
*/

/* duplamente encadeada circular
typedef int TipoItem; // tipo dos elementos na lista

typedef struct no { //estrutura para
//lista duplamente encadeada circular
    TipoItem info;
    struct no * ant; // ponteiro para o elemento anterior
    struct no * prox; // ponteiro para pr´oximo elemento
} Lista;
*/

/* encadeada com cabeça e cauda
ypedef int TipoItem;
struct no { // estrutura de n´o para lista encadeada
TipoItem info;
struct no * prox;
};
typedef struct { // estrutura para lista encadeada com cabe¸ca e cauda
struct no* cabeca;
struct no* cauda;
} Lista;
*/

/* FILA USANDO LISTA ENCADEADA
typedef int TipoItem;

struct no {
    TipoItem info;
    struct no* prox;
};

typedef struct {
    struct no* inicio;
    struct no* fim;
} Fila;

Int vazia(Fila* f) {
return (f->inicio == NULL);
}
Fila* cria_fila_vazia() {
Fila* f = (Fila*) malloc(sizeof(Fila));
f->inicio = NULL;
f->fim = NULL;
return f;

//Enfileira um elemento
void enqueue(Fila* f, TipoItem x) {
struct no* aux = (struct no*) malloc(sizeof(struct no));
aux->info = x;
aux->prox = NULL;
if(vazia(f)) {
f->inicio = aux;
}
else {
f->fim->prox = aux;
}
f->fim = aux;
}

}

//Desenfileira um elemento
TipoItem* dequeue(Fila* f) {
if(!vazia(f)) {
TipoItem* x = (TipoItem*) malloc(sizeof(TipoItem));
struct no* aux = f->inicio;
*x = f->inicio->info;
if(f->inicio == f->fim) // s´o tem 1 elemento
f->fim = NULL;
f->inicio = f->inicio->prox;
free(aux);
return x;
}
else return NULL;
}


typedef int TipoItem;
// estrutura para lista encadeada
struct no {
TipoItem info;
struct no* prox;
};
// estrutura de lista com cabe¸ca
// para implementa¸c~ao de pilha
typedef struct {
struct no* topo;
} Pilha;

int vazia(Pilha* p) {
return (p->topo == NULL);
}
Pilha* criar_pilha_vazia() {
Pilha* aux = (Pilha*) malloc(sizeof(Pilha));
aux->topo = NULL;
return aux;
}

// L^e o topo da pilha sem desempilhar
TipoItem* topo(Pilha* p) {
if(!vazia(p)) {
TipoItem* x = (TipoItem*) malloc(sizeof(TipoItem));
*x = p->topo->info;
return x;
}
else return NULL;
}

// Empilha um item
void push(Pilha* p, TipoItem x) {
struct no* aux = (struct no*) malloc(sizeof(struct no));
aux->info = x;
aux->prox = p->topo;
p->topo = aux;
}

//Desempilha um item
TipoItem* pop(Pilha* p) {
if(!vazia(p)) {
TipoItem* x = (TipoItem*) malloc(sizeof(TipoItem));
struct no* aux = p->topo;
*x = p->topo->info;
p->topo = p->topo->prox;
free(aux);
return x;
}
else {
printf("Pilha vazia!");
return NULL;
}
}

*/

int vazia(Lista* l){
    return (l==NULL);
}

Lista* inserir(Lista* l, int info){
    Lista* aux = (Lista*) malloc(sizeof(Lista));
    aux->info = info;
    aux->prox = l; 

    return aux;
}

Lista* inserir_cauda(Lista* l, int info){
    if(l == NULL){
        Lista* aux = (Lista*)malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = NULL;
        return aux;
    }else {
        l->prox = inserir_cauda(l->prox, info);
        return l;
    }
}

void imprimeLista(Lista* l){
    if(l!= NULL){ 
        printf("%d - ",l->info);
        imprimeLista(l->prox);
    }else printf("NULL");
}


int somar_intervalo(Lista* l, int a, int b){
if(l==NULL){   return 0;  }

    if(l->info >= a && l->info <= b){
        return l->info + somar_intervalo(l->prox, a, b);
    }else 
        return somar_intervalo(l->prox,a,b);
}

//soma multiplos de um numero n
int somar_multiplos(Lista* l, int n){
    if(l==NULL){
        return 0;
    }

    if(l->info % n == 0){
        return l->info + somar_multiplos(l->prox, n);
    }

return somar_multiplos(l->prox, n);
}

//insere um elemento apos um valor de referencia ou no fim da lista
    //caso o valor de referencia nao esteja na lista
//pos condição: elemento inserido apos valor de referencia
Lista* inserir_apos(Lista* l, int valref, int info){
    if(vazia(l)){ return NULL; }

    Lista* aux = l;
    while(aux != NULL){
        if(aux->info == valref){
            Lista* novo = (Lista*)malloc(sizeof(Lista));
            novo->info = info;
            //novo->prox = NULL; desnecessary

            novo->prox = aux->prox;
            aux->prox = novo;
            return l;
        }
        aux = aux->prox; 
    }
    return inserir_cauda(l, info);
}

//versao recursiva
Lista* inserir_apos_rec(Lista* l, int valref, int info){
    if(vazia(l)){ 
    l = inserir_cauda(l, info);
    return l;
    }

    if(l->info == valref){
        Lista* aux = (Lista*)malloc(sizeof(Lista));
        aux->info = info;
        aux->prox = l->prox;
        l->prox = aux;
        return l;
    }

    l->prox = inserir_apos_rec(l->prox, valref, info);
    return l;
}


//função para inserir antes do valor de referencia, caso nao tenha insira no final da lista
Lista* inserir_antes(Lista* l, int valref, int info){
    if(vazia(l)) {
    l = inserir_cauda(l, info);
    return l;
    }

  if(l->info == valref){
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->info = info;
    novo->prox = l;
    return novo;
  }

l->prox = inserir_antes(l->prox, valref, info);

return l;
}


//remove qualquer elemento da lista
Lista* remove_elemento(Lista* l, int info){
    if(vazia(l)){
        return l;
    }

    if(l->info == info){
        Lista* aux = l->prox;
        free(l);
        return aux;        
    }
    l->prox = remove_elemento(l->prox, info);

    return l;
}


//remove de uma lista os elementos pertencentes a outra lista
//pos condição: l1 nao contem elementos de l2
Lista* subtrair(Lista* l1, Lista* l2){
    if(vazia(l1) || vazia(l2)){
        return l1;
    }

    Lista* aux = l2;
    while(aux != NULL){
        l1 = remove_elemento(l1, aux->info);
        aux = aux->prox;
    }
    return l1;
}

//retorna o valor maximo presente na lista
//retorno: valor maximo presente ou -1 caso seja vazia
int maximo(Lista* l){ //recursiva
    if(l == NULL){
        return -1;
    }

    // Caso recursivo: encontrar o máximo na sublista
    int max_prox = maximo(l->prox);  // Encontra o máximo na sublista
    // Compara o valor do nó atual com o máximo da sublista
    if (l->info > max_prox) {
        printf("-%d-\n", l->info);
        return l->info;  // Retorna o valor do nó atual se for maior
    } else {
        printf("--%d--\n", max_prox);
        return max_prox;  // Retorna o máximo da sublista
    }
}

int maximo_iterativo(Lista* l){ //mais facil de se entender
    if(l == NULL){ return -1; }

    int max = l->info;
    Lista* aux = l;

    while(aux != NULL){
        if(aux->info > max){
            max = aux->info;
        }
        aux = aux->prox;
    }
return max;
}

//cria uma lista com os numeros impares da lista reformada
//pos condição: retorna uma nova lista com os numeros impares
//              mantendo a lista original inalterada
Lista* impares(Lista* l){ //sempre que quiser fazer uma nova lista, é necessario uma inserção
    Lista* aux = l;
    Lista* nova_lista = NULL;

    while(aux != NULL){
        if((aux->info % 2) == 1){
            nova_lista = inserir(nova_lista, aux->info);
        }
        aux = aux->prox;
    }
return nova_lista;
}

//remove os elementos que estejam em um intervalo fechado dado
//pos condição: lista modificada sem numeros no intervalo fechado[a,b]
Lista* remove_intervalo(Lista* l, int a, int b){
    if(l == NULL){
        return NULL;
    }
    
    if(l->info >= a && l->info <= b){
        Lista* aux = l;
        l = remove_intervalo(l->prox, a, b);
        free(aux);
    }else{
        l->prox = remove_intervalo(l->prox, a, b);
    }
return l;
}

struct no* remover_ocorrencias(struct no* l, int x){
    if(l == NULL) return NULL;
        if (l->info == x) { // Se o nó atual contém x, remove ele
            struct no* temp = l; 
            l = l->prox; // Avança para o próximo nó
            free(temp); 
            return remover_ocorrencias(l, x); // Chama recursivamente com a nova cabeça
        }
    
        l->prox = remover_ocorrencias(l->prox, x); // Continua para o próximo nó
        return l;
}

//retorna uma lista que contem os elementos das posições no intervalo [pos1,pos2]
//pre condição: pos1 <= pos2 e pos1>=0
//pos condição:gera uma lista com os elementos que ocupam as posições
//no intervalo [pos1,pos2], considerando a cabeça da lista como posição 0.
//Os elementos da lista gerada estão na mesma ordem da lista original.
//A lista original não é modificada.
Lista* obter_subLista(Lista* l, int pos1, int pos2){
    if (l == NULL || pos1 > pos2) {
        return NULL;  // Caso base: lista vazia ou intervalo inválido
    }

    // Ignora os primeiros elementos até alcançar pos1
    if (pos1 > 0) {
        return obter_subLista(l->prox, pos1 - 1, pos2 - 1);
    }

    // Quando pos1 == 0, começa a construir a sublista
    Lista* sublista = NULL;
    sublista = inserir_cauda(sublista, l->info);

    // Se ainda há elementos no intervalo [pos1, pos2], continue
    if (pos2 > 0 && l->prox != NULL) {
        Lista* restoSublista = obter_subLista(l->prox, 0, pos2 - 1);
        sublista->prox = restoSublista;    }
    return sublista;
}


//insere info na lista ordenada (recursiva)

Lista* inserir_ordenado(Lista* l, int info){
    if(l == NULL || info < l->info){
        Lista* novo = (Lista*)malloc(sizeof(Lista));
        novo->info = info;
        novo->prox = l;
        return novo;
    }

    l->prox = inserir_ordenado(l->prox, info);
    return l;
}

//inverte uma lista 
Lista* inverter(Lista* l){
    Lista* nova = NULL;
    Lista* aux = l;

    while(aux != NULL){
        nova = inserir(nova, aux->info);
        aux = aux->prox;
    }
return nova;
}

//concatenar duas listas
Lista* concatenar(Lista* l1, Lista* l2){
    if(l1 == NULL){
        return l2;
    }
    l1->prox = concatenar(l1->prox, l2);
    return l1;
}
//intercalar duas listas
Lista* intercalar(Lista* l1, Lista* l2){
    if(l1 == NULL){
        return l2;
    }
    if(l2 == NULL){
        return l1;
    }

    Lista* nova = (Lista*)malloc(sizeof(Lista));
    nova->info = l1->info;
    nova->prox = intercalar(l2, l1->prox);
    return nova;
}




int main(){

Lista* x = NULL;
Lista* y = NULL;

/*
x = inserir_cauda(x, 1);
x = inserir_cauda(x, 3);
x = inserir_cauda(x, 5);
x = inserir_cauda(x, 8);
x = inserir_cauda(x, 6);
y = inserir_cauda(y, 1);
y = inserir_cauda(y, 6);
y = inserir_cauda(y, 7);
y = inserir_cauda(y, 3);*/

y = inserir(y, 1);
y = inserir(y, 3);
y = inserir(y, 5);
y = inserir(y, 8);
y = inserir(y, 6);

   printf("\n\n");
imprimeLista(y);
printf("\n\n");
//imprimeLista(y);
//printf("\n\n");
//int soma;
//soma = somar_intervalo(x, 2, 5);
//soma = somar_multiplos(x, 2);
//soma = maximo(x);
//soma = maximo_iterativo(x);
//x = impares(x);
//x = remove_intervalo(x, 2, 7);
//x = inserir_apos_rec(x, 4, 22);
//x = inserir_antes(x, 2, 23);
//printf("soma do intervalo = %d", soma);
//printf("soma multiplo de 2 = %d", soma);
//printf("maximo desta lista eh %d", soma);
//printf("impares\n");

//x = subtrair(x, y);
//x = obter_subLista(x, 2, 6);
x = remover_ocorrencias(y, 3);


imprimeLista(x);

printf("\n\n");
    return 0; 
}