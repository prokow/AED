#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no* esq;
    struct no* dir;
};

typedef struct no* arvore;

int vazia(arvore r){
    return (r==NULL);
}

int maximo(arvore r){
    if(r->dir == NULL){ //recursiva
      return r->info;
    } return maximo(r->dir);

    /*while(r->dir != NULL)
        r = r->dir;     INTERATIVA
    return r->info;*/
}

int minimo(arvore r){
    if(r->esq == NULL){ //recursiva
        return r->info;
    } return minimo(r->esq);

    /*while(r->esq != NULL)
        r = r->info;   INTERATIVA
    return r->info;*/
}

arvore inserir(arvore r, int x){
    if(vazia(r)){
        r = (struct no*) malloc(sizeof(struct no));
        r->info = x;
        r->esq = NULL;
        r->dir = NULL;
    }
    else if(x < r->info)
        r->esq = inserir(r->esq, x);
        else
            r->dir = inserir(r->dir, x);
    return r;
}


arvore busca(arvore r, int x){
    if(vazia(r)) return NULL;
    if(r->info > x) return busca(r->esq, x);
    if(r->info < x) return busca(r->dir, x);
    return r;
}


arvore remover(arvore r, int x){
    
    if(!vazia(r)){
        if(x < r->info) 
            r->esq =  remover(r->esq, x);
        else if(x > r->info) 
            r->dir = remover(r->dir, x);
        else //x == r->info
            if(r->esq == NULL && r->dir == NULL){
                free(r);
                r = NULL;
            }
            else if(r->esq == NULL){
                r->info = minimo(r->dir);
                r->dir = remover(r->dir, r->info);
            }
            else {
                r->info = maximo(r->esq);
                r->esq = remover(r->esq, r->info);
            }
    return r;
    }
return NULL;
}




void in_ordem(arvore r){  
    if(!vazia(r)){
        in_ordem(r->esq);
        printf("%d ", r->info);
        in_ordem(r->dir);
    }
}

void pre_ordem(arvore r){
    if(!vazia(r)){
        printf("%d ",r->info);
        pre_ordem(r->esq);
        pre_ordem(r->dir);
    }
}

void pos_ordem(arvore r){
    if(!vazia(r)){
        pos_ordem(r->esq);
        pos_ordem(r->dir);
        printf("%d ", r->info);
    }
}

int somaTotal(arvore r){
    if(!vazia(r)){
            return r->info + somaTotal(r->esq) + somaTotal(r->dir);
    }
    return 0;
}


int altura(arvore r){
    if(!vazia(r)){
        int altura_esq = altura(r->esq);
        int altura_dir = altura(r->dir);
        return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
        //verifica qual altura é maior
        //se altura_esq for maior, retorna a da esquerda; Senão retorna a da direita; assim escolhendo a subarvore mais profunda
        // +1 é para contar o nó em especifico
    }
    return 0;
}


// 5. Considerando o c´odigo do exerc´ıcio anterior, implemente a fun¸c˜ao imprimir por niveis que imprime
// as chaves por n´ıveis.

void imprimePorNiveis(arvore r) {
    if (r == NULL) return;

    // Calcula a altura da árvore para saber quantos níveis temos
    int h = altura(r) + 1;

    // Cria uma fila para armazenar os nós
    arvore fila[100];
    int inicio = 0, fim = 0;

    // Enfileira o nó raiz
    fila[fim++] = r;

    // Loop para percorrer todos os níveis
    for (int nivel = 0; nivel < h; nivel++) {
        int numNosNoNivel = fim - inicio; // número de nós no nível atual

        // Processa todos os nós do nível atual
        for (int i = 0; i < numNosNoNivel; i++) {
            arvore atual = fila[inicio++];

            // Imprime o valor do nó atual
            printf("%d ", atual->info);

            // Enfileira os filhos do nó atual
            if (atual->esq != NULL) fila[fim++] = atual->esq;
            if (atual->dir != NULL) fila[fim++] = atual->dir;
        }

        // Pula para uma nova linha após imprimir um nível completo
        printf("\n");
    }
}



//6. Implemente um algoritmo para determinar se uma ´arvore bin´aria ´e cheia
void verificaArvoreCheia(arvore r){
  if(vazia(r)){
    return;
  }
  int altEsq = altura(r->esq);
  int altDir = altura(r->dir);

  if(altEsq == altDir){
    printf("A arvore esta cheia\n");
  }else printf("A arvore nao esta cheia\n");
}
//outro jeito
int arvoreCheia(arvore r) {
    // Caso base: se o nó for NULL, ele é considerado parte de uma árvore cheia
    if (r == NULL) return 1;

    // Caso em que o nó é uma folha (sem filhos)
    if (r->esq == NULL && r->dir == NULL) return 1;

    // Caso em que o nó tem ambos os filhos
    if (r->esq != NULL && r->dir != NULL)
        return arvoreCheia(r->esq) && arvoreCheia(r->dir);

    // Se o nó tem apenas um filho, a árvore não é cheia
    return 0;
}


//7. Implemente um algoritmo para determinar se uma ´arvore bin´aria ´e estritamente bin´aria.
// Função para verificar se a árvore é estritamente binária
int verificaEstritamenteBinario(arvore r){
if(vazia(r)){
  return 1; //arvore vazia é estritamente binario
}

  if((r->esq == NULL && r->dir != NULL) || (r->esq != NULL && r->dir == NULL)){
    return 0; //nó com apenas um filho
  }

return verificaEstritamenteBinario(r->esq) && verificaEstritamenteBinario(r->dir);  
}
//Uma árvore binária é considerada estritamente binária (ou binária completa) se cada nó tem exatamente 0 ou 2 filhos. 
//Isso significa que todos os nós internos (nós que não são folhas) devem ter dois filhos, e os nós folha não devem ter filhos.


void imprimir_intervalos(arvore r, int a, int b){ //intervalo fechado
    if(!vazia(r)){

        if(r->info > a){ imprimir_intervalos(r->esq, a, b);  }

        if(r->info >= a && r->info <= b){
            imprimir_intervalos(r->esq, a, b);
            printf("%d ", r->info);
            imprimir_intervalos(r->dir, a, b);
        }

        if(r->info < b){ imprimir_intervalos(r->dir, a, b);  }
    }
}

//função seguinte: retorna o menor valor maior que k presente na arvore, supondo que k pertence a arvore. caso nao exista, retorna -1
int seguinte(arvore r, int k) {
    arvore proximo = NULL; // Variável para armazenar o próximo maior

    while (r != NULL) {
        if (r->info > k) {
            proximo = r; // Atualiza o próximo maior se o valor for maior que k
            r = r->esq; // Procura na subárvore esquerda para encontrar um possível menor
        } else {
            r = r->dir; // Se o valor não for maior que k, vai para a subárvore direita
        }
    }

    return (proximo != NULL) ? proximo->info : -1; // Retorna o próximo maior ou -1
}

//retorna o numero de nos internos (nao-folhas)
int contaNosInternos(arvore r){
    if(vazia(r)){ return 0;}
    
    if(r->esq != NULL || r->dir != NULL){
        return 1 + contaNosInternos(r->esq) + contaNosInternos(r->dir);
    }

return 0;
}

//retorna a soma dos elementos cujo valor seja maior que k. considere que a arvore seja uma arvorie binaria de busca
int somaMaiores(arvore r, int k){
    if(vazia(r)){ return 0;}

    if(r->info > k){
        return r->info + somaMaiores(r->esq, k) + somaMaiores(r->dir, k);
    } else {
        return somaMaiores(r->dir, k);
    }
}


//retorna o numero de nós que tem um unico filhozz  
int contaNoscomFilhoUnico(arvore r){
    if(vazia(r)){ return 0; }

    if((r->esq != NULL && r->dir == NULL) || (r->esq == NULL && r->dir != NULL)){
        return 1 + contaNoscomFilhoUnico(r->esq) + contaNoscomFilhoUnico(r->dir);
    }
        return contaNoscomFilhoUnico(r->esq) + contaNoscomFilhoUnico(r->dir);
}

void imprimeMultiplosDeDois(arvore r) {
    if (r == NULL) {
        return;  // Caso base: nó vazio
    }

    // Verifica se o valor do nó é múltiplo de 2
    if (r->info % 2 == 0) {
        printf("%d ", r->info);  // Imprime o valor se for múltiplo de 2
    }

    // Chama a função recursivamente nas subárvores
    imprimeMultiplosDeDois(r->esq);
    imprimeMultiplosDeDois(r->dir);
}


//[11,[5,[2,[],[]],[8,[],[]]],[14,[],[22,[15,[],[]],[]]]] pre_ordem
void imprime(arvore r){
    if(!vazia(r)){
        printf("[%d", r->info);
    
    if(r->esq != NULL || r->dir != NULL){
        printf(",");

        if(r->esq != NULL){
            imprime(r->esq);
        }else{
            printf("[]");
        }

        if(r->dir != NULL){
            printf(",");
            imprime(r->dir);
        }else {
            printf(",[]");
        }
    }
    printf("]");
    }
}


// Função que retorna a maior chave que é menor que k
int anterior(arvore r, int k) {
    arvore anterior = NULL; // Variável para armazenar o anterior maior

    while (r != NULL) {
        if (r->info < k) {
            anterior = r; // Atualiza o anterior se o valor for menor que k
            r = r->dir;   // Procura na subárvore direita para encontrar um possível maior
        } else {
            r = r->esq;   // Se o valor não for menor que k, vai para a subárvore esquerda
        }
    }

    return (anterior != NULL) ? anterior->info : -1; // Retorna o anterior maior ou -1
}

int main(){

arvore r = NULL;

r = inserir(r, 8);
r = inserir(r, 6);
r = inserir(r, 4);
r = inserir(r, 2);
r = inserir(r, 1);
//r = inserir(r, 12);


//printf("em ordem: ");
//in_ordem(r);
printf("\n");
imprimePorNiveis(r);

//verificaArvoreCheia(r);

/*
int cheia = arvoreCheia(r);
    if(cheia == 1){
        printf("arvore esta cheia\n");
    }else printf("arvore nao esta cheia\n");
*/

//int soma = somaTotal(r);
//printf(" Soma total = %d\n", soma);

//int somaMaior = somaMaiores(r, 2);
//printf(" Soma total do numero maior que 2 = %d\n", somaMaior);

//int a = contaNosInternos(r);
//printf(" Quantidade de No's Internos = %d\n", a);


/*int y = contaNoscomFilhoUnico(r);
printf(" Quantidade de No's com filho unico = %d\n", y);
*/
imprime(r);

printf("\n");

int z = seguinte(r, 8);
printf(" seguinte  = %d\n", z);

int b = anterior(r, 1);
printf(" anterior  = %d\n", b);

printf("maximo %d e minimo %d desta arvore\n",maximo(r),minimo(r));

imprimir_intervalos(r, 2,6);

printf("\n");
    return 0;
}



/*
3. Uma implementa¸c˜ao poss´ıvel para ´arvores bin´arias ´e utilizando um vetor alocado estaticamente que
comporta no m´aximo n nodos, tal que a raiz est´a sempre localizada na posi¸c˜ao 0. Al´em disso, dado um
n´o da posi¸c˜ao i, o filho `a esquerda est´a na posi¸c˜ao 2i+1 e o filho `a direita na posi¸c˜ao 2i+2. Considerando
essa implementa¸c˜ao, caracterize a situa¸c˜ao em que o vetor est´a completamente preenchido. Tamb´em
calcule a altura m´axima que a ´arvore pode ter considerando um vetor com n posi¸c˜oes.


4. Considere o c´odigo abaixo:
struct no { // estrutura de n´o para ´arvore bin´aria
int info;
struct no* esq;
struct no* dir;
};
typedef struct no* arvore;
int vazia(arvore r){
return (r == NULL);
}


Implemente as seguintes fun¸c˜oes, tanto de maneira recursiva quanto iterativa:
(a) inserir que insere uma chave dada como entrada. x
(b) remover que remove uma chave dada como entrada. x
(c) in ordem que imprime as chaves fazendo o percorrimento in ordem. x
(d) pre ordem que imprime as chaves fazendo o percorrimento pr´e-ordem. x
(e) pos ordem que imprime as chaves fazendo o percorrimento p´os-ordem. x
(f) maximo que retorna o valor da maior chave. x
(g) minimo que retorna o valor da menor chave. x
(h) altura que retorna a altura da ´arvore bin´aria. 
(i) soma que retorna a soma de todas as chaves.

*/