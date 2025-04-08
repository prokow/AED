#include <stdio.h>
#include <stdlib.h>


struct no23{
    int chave_esq;
    int chave_dir;
    struct no23* esq;
    struct no23* meio;
    struct no23* dir;
    int n;
};

typedef struct no23* arvore23;

int vazia (arvore23 r){
    return (r == NULL);
}

arvore23 busca(arvore23 r, int x){
    if(vazia(r)){
        return NULL;
    }
    if(r->chave_esq == x){
        return r;
    }
    if(r->n == 2 && r->chave_dir == x){
        return r;
    }
    if(r->chave_esq > x){
        return busca(r->esq, x);
    }
    else if(r->n == 1){
        return busca(r->meio, x);
    }else if(r->chave_dir > x){
        return busca(r->meio, x);

    }else return busca(r->dir, x);
}

arvore23 criaNo23(int chave_esq, int chave_dir, arvore23 esq, arvore23 meio, arvore23 dir, int n) {
    arvore23 novo = (arvore23) malloc(sizeof(struct no23));
    if (novo == NULL) {
        printf("Erro: memória insuficiente!\n");
        exit(1);
    }

    novo->chave_esq = chave_esq;
    novo->chave_dir = (n == 2) ? chave_dir : 0;
    novo->esq = esq;
    novo->meio = meio;
    novo->dir = (n == 2) ? chave_dir : 0;
    novo->n = n; // número de chaves (1 ou 2)
    
    return novo;
}


int eh_folha(arvore23 p) {
    return (p->esq == NULL && p->meio == NULL && p->dir == NULL);
}

arvore23 split(arvore23 p, int chave, arvore23 subarvore,int *chave_promovida){
    arvore23 paux;

    if (chave > p->chave_dir) { // chave ficar´a mais a direita
        *chave_promovida = p->chave_dir; // promove a antiga maior
        paux = p->dir;
        p->dir = NULL; // elimina o terceiro filho
        p->n = 1; // atualiza o n´umero de chaves
    return criaNo23(chave, 0, paux, subarvore, NULL, 1);
    }

    if (chave >= p->chave_esq){ // chave est´a no meio
        *chave_promovida = chave; // continua sendo promovida
        paux = p->dir;
        p->dir = NULL;
        p->n = 1;
    return criaNo23(p->chave_dir, 0, subarvore, paux, NULL,1);
    }

    // chave ficar´a mais `a esquerda
    *chave_promovida = p->chave_esq;
    // primeiro cria o n´o `a direita
    paux = criaNo23(p->chave_dir, 0, p->meio, p->dir, NULL,1);
    p->chave_esq = chave; // atualiza o n´o `a esquerda
    p->n = 1;
    p->dir = NULL;
    p->meio = subarvore;

    return paux;
}

// Adiciona uma chave em um n´o que tem 1 chave
// Pr´e-condi¸c~ao: n´o r tem somente uma chave
// P´os-condi¸c~ao: insere chave no n´o r com sub´arvore p
void adicionaChave(arvore23 r, int chave, arvore23 p) {
    if(r->chave_esq < chave) {
        r->chave_dir = chave;
        r->dir = p;
    }
    else {
        r->chave_dir = r->chave_esq;
        r->chave_esq = chave;
        r->dir = r->meio;
        r->meio = p;
    }
    r->n = 2;
}

//Insere uma chave em uma ´arvore 2-3 retornando n´o gerado pelo split e
// a chave a ser promovida
// Pr´e-condi¸c~ao: raiz n~ao vazia
// P´os-condi¸c~ao: chave inserida em alguma sub´arvore de r
// Retorno: n´o gerado no split e chave promovida ou NULL caso n~ao tenha
// ocorrido split
arvore23 inserir_aux(arvore23 r, int chave, int* chave_promovida) {
    if(eh_folha(r)){ // caso base: est´a em uma folha
        if(r->n == 1) {
            adicionaChave(r,chave,NULL);
        return NULL;
        }
    else return split(r, chave, NULL, chave_promovida);
    }
    else { // precisa descer

    arvore23 paux;
    int ch_aux;

    if (chave < r->chave_esq)  
        paux = inserir_aux(r->esq, chave, &ch_aux);
    else if ((r->n == 1) || (chave < r->chave_dir)) 
        paux = inserir_aux( r->meio, chave, &ch_aux);
    else
        paux = inserir_aux(r->dir, chave, &ch_aux);
    if (paux == NULL) // nao promoveu
        return NULL;
    if (r->n == 1){
        adicionaChave(r, ch_aux, paux);
    return NULL;
    }
    else // precisa fazer split
        return split(r, ch_aux, paux,chave_promovida);
    }
}


arvore23 inserir(arvore23 r, int chave){
    if(vazia(r)) // caso base especial: a ´arvore ´e vazia
        return criaNo23(chave,0,NULL,NULL,NULL,1);
    else {

    int chave_promovida;
    arvore23 aux = inserir_aux(r,chave,&chave_promovida);

    if(!vazia(aux)) // cria nova raiz
        return criaNo23(chave_promovida, 0,r,aux,NULL,1);
    else // raiz n~ao se altera
        return r;
    }
}

/*
void imprimeArvore(arvore23 r, int nivel) {
    if (r == NULL) return;

    // Indenta conforme o nível da árvore
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    // Exibe as chaves do nó atual
    if (r->n == 1) {
        printf("[%d]\n", r->chave_esq);
    } else if (r->n == 2) {
        printf("[%d, %d]\n", r->chave_esq, r->chave_dir);
    }

    // Recursivamente imprime os filhos
    imprimeArvore(r->esq, nivel + 1);
    imprimeArvore(r->meio, nivel + 1);
    imprimeArvore(r->dir, nivel + 1);
}*/

void imprimeArvore(arvore23 r, int nivel) {
    if (vazia(r)) return;
    printf("Nivel %d: ", nivel);
    printf("[%d", r->chave_esq);

    if (r->n == 2) printf(", %d", r->chave_dir);
    printf("]\n");

    imprimeArvore(r->esq, nivel + 1);
    imprimeArvore(r->meio, nivel + 1);
    
    if (r->n == 2) imprimeArvore(r->dir, nivel + 1);
}



int minimo(arvore23 r) {
    if(!vazia(r)){
        if(eh_folha(r)){
            return r->chave_esq;
        }
        return minimo(r->esq);
    } 
    return -1;
}


int maximo(arvore23 r){
    if(!vazia(r)){
        if(eh_folha(r)){
            if(r->n == 1){
                return r->chave_esq;
            }
            return r->chave_dir;
        }

        if(r->n == 1){
            return maximo(r->meio);
        }
        return maximo(r->dir);
    }
    return -1;
}


void in_ordem(arvore23 r){
    if(vazia(r)) return;

    in_ordem(r->esq);
    printf("%d ", r->chave_esq);
    in_ordem(r->meio);
    if(r->n == 2){
        printf("%d ", r->chave_dir);
    }
    in_ordem(r->dir);
}



void inverter(arvore23 r) {
    if (vazia(r) || eh_folha(r)) return; // Caso base: árvore vazia ou folha, nada a inverter

    // Troca os ponteiros dos filhos
    if (r->n == 1) { // Nó com um filho esquerdo e um filho do meio
        arvore23 temp = r->esq;
        r->esq = r->meio;
        r->meio = temp;
    } else if (r->n == 2) { // Nó com três filhos (esq, meio e dir)
        arvore23 temp = r->esq;
        r->esq = r->dir;
        r->dir = temp;
        // O filho do meio permanece no centro
    }

    // Recursivamente inverte os filhos
    inverter(r->esq);
    inverter(r->meio);
    if (r->n == 2) inverter(r->dir);
}


int somarTodos(arvore23 r) {
    if (vazia(r)) return 0;  // Se a árvore estiver vazia, retorna 0

    int soma = 0;
    soma += r->chave_esq; // Adiciona a chave esquerda

    if (r->n == 2) {
        soma += r->chave_dir; // Adiciona a chave direita, se presente
    }

    // Soma recursivamente nos filhos
    soma += somarTodos(r->esq);
    soma += somarTodos(r->meio);
    if (r->n == 2) soma += somarTodos(r->dir);

    return soma;
}

int somarMaiores(arvore23 r, int x) {
    if (vazia(r)) return 0;  // Se a árvore estiver vazia, retorna 0

    int soma = 0;
    
    // Verifica e soma a chave esquerda
    if (r->chave_esq >= x) {
        soma += r->chave_esq;
    }

    // Verifica e soma a chave direita, se presente
    if (r->n == 2 && r->chave_dir >= x) {
        soma += r->chave_dir;
    }

    // Soma recursivamente nos filhos
    soma += somarMaiores(r->esq, x);
    soma += somarMaiores(r->meio, x);
    if (r->n == 2) soma += somarMaiores(r->dir, x);

    return soma;
}


int contaNosInternos(arvore23 r){
    if (vazia(r) || eh_folha(r)) {
        return 0;
    }

    return 1 + contaNosInternos(r->esq) + contaNosInternos(r->meio) + contaNosInternos(r->dir);
}

int conta_nos(arvore23 r){
    if(vazia(r)) return 0;

    return 1 + conta_nos(r->esq) + conta_nos(r->meio) + conta_nos(r->dir);
}




//Implemente a função que retorna o nó com a chave k
int noCHAVE(arvore23 r, int k){
    if(vazia(r)){return 0;}

    if(r->chave_esq == k){
        return r->chave_esq;
    }

    if(r->n == 2){
        if(r->chave_dir == k){
            return r->chave_dir;
        }
    }
    return noCHAVE(r->esq,k) + noCHAVE(r->meio,k) + noCHAVE(r->dir,k);
}



void imprimirMultiplo(arvore23 r, int x){
    if(!vazia(r)){
        if(r->chave_esq % x == 0){
            printf("%d eh multiplo de %d\n", r->chave_esq, x);
        }
        if((r->n == 2) && (r->chave_dir % x == 0)){
            printf("%d eh multiplo de %d\n", r->chave_dir, x);
        }

        imprimirMultiplo(r->esq,x);
        imprimirMultiplo(r->meio,x);
            
        if(r->n == 2){
            imprimirMultiplo(r->dir,x);
        }
    }
}

void imprimirIntervalo(arvore23 r, int a, int b){
    if(!vazia(r)){

        imprimirIntervalo(r->esq,a,b);

        if(r->chave_esq >= a && r->chave_esq <= b){
            printf("%d ",r->chave_esq);
        }

        imprimirIntervalo(r->meio,a,b);



        if(r->n == 2){
            if(r->chave_dir >= a && r->chave_dir <= b){
                printf("%d ", r->chave_dir);
            }
            imprimirIntervalo(r->dir,a,b);  

        }

    }
}



int main(){
    arvore23 raiz = NULL; // Inicializa a árvore vazia

    // Inserindo chaves na árvore 2-3
    int chaves[] = {60, 20, 10, 30, 25, 50, 80};
    int n_chaves = sizeof(chaves) / sizeof(chaves[0]);

    for (int i = 0; i < n_chaves; i++) {
        raiz = inserir(raiz, chaves[i]);
        printf("Após inserir %d:\n", chaves[i]);
        imprimeArvore(raiz, 0);
        printf("\n");
    }
    /*
    int min = minimo(raiz);
    printf("Minimo: %d\n", min);

    int max = maximo(raiz);
    printf("Maximo: %d\n", max);
    */

   /*
    int contaNOS = conta_nos(raiz);
    printf("O numero de nos nessa arvore é %d\n",contaNOS);
    */

   //in_ordem(raiz);
   imprimirIntervalo(raiz, 15, 80);
   //imprimirMultiplo(raiz,2);
    printf("\n");

/*
    int chave = noCHAVE(raiz,80);
    printf("%d\n", chave);
*/

    int contaNosInterno = contaNosInternos(raiz);
    printf("Nos internos => %d\n",contaNosInterno);


    return 0;
}