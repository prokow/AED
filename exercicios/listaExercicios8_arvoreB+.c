#include <stdio.h>
#include <stdlib.h>

#define ORDEM 5
//estrutura de n´o para ´arvore B+


typedef struct nodeBMais {
void * ponteiro[ORDEM]; // vetor de ponteiros
int chave[ORDEM-1]; // vetor de chaves
struct nodeBMais * pai; // ponteiro para o n´o-pai
int eh_folha; // booleano, verdadeiro quando n´o ´e folha
int numChaves; // n´umero de chaves no n´o
} noBMais;


/*
ponteiro ´e um vetor de ponteiros do tipo void, podendo apontar tanto para sub´arvores quanto
para dados sat´elites relacionados `as chaves.
• chave ´e um vetor de inteiros para armazenar as chaves.
• pai ´e um ponteiro para o n´o-pai visando facilitar as opera¸c˜oes de inser¸c˜ao e remo¸c˜ao.
• se eh folha ´e verdadeiro ent˜ao ponteiro[ORDEM] guarda o endere¸co do n´o-folha `a direita.
Implemente fun¸c˜oes para inser¸c˜ao, busca, remo¸c˜ao e percorrimento in-ordem na ´arvore B+
*/

//contarFolhas -> dada a raiz r, retorna o numero de folhas evitando percorrer em nós desnecessarios
//imprimeFolhasIntervalo(r, a, b) -> imprime as chaves das folhas da arvore B+ que estao no intervalo [a, b]. Evitando percorrer nós desnecessarios
/*começo da lógica

if(!vazia(r)){
    if(r->eh_folha==0){
    for(int i=0; i<r->numChaves && r->chave[i] <= b; i++){
        if(r->chave[i] >= a){
            print("%d", r->chave[i]);
        }else
    }
}

*/

// Função para verificar se a árvore está vazia
int vazia(noBMais *r) {
    return r == NULL;
}

// Função para criar um novo nó
noBMais *criarNo(int eh_folha) {
    noBMais *novo = (noBMais *)malloc(sizeof(noBMais));
    novo->eh_folha = eh_folha;
    novo->numChaves = 0;
    novo->pai = NULL;
    for (int i = 0; i < ORDEM; i++) {
        novo->ponteiro[i] = NULL;
    }
    return novo;
}

// Função para buscar a posição correta da chave no nó
int buscarPosicao(noBMais *n, int chave) {
    int i = 0;
    while (i < n->numChaves && n->chave[i] < chave) {
        i++;
    }
    return i;
}

// Função para inserir uma chave no nó
void inserirChaveNo(noBMais *n, int chave, void *ponteiro) {
    int pos = buscarPosicao(n, chave);
    for (int i = n->numChaves; i > pos; i--) {
        n->chave[i] = n->chave[i - 1];
        n->ponteiro[i + 1] = n->ponteiro[i];
    }
    n->chave[pos] = chave;
    n->ponteiro[pos + 1] = ponteiro;
    n->numChaves++;
}

// Função para dividir um nó quando ele estiver cheio
void dividirNo(noBMais *n, noBMais *pai, int pos) {
    noBMais *novo = criarNo(n->eh_folha);
    int meio = n->numChaves / 2;
    int chavePromovida = n->chave[meio];

    // Mover as chaves e ponteiros para o novo nó
    novo->numChaves = n->numChaves - meio - 1;
    for (int i = 0; i < novo->numChaves; i++) {
        novo->chave[i] = n->chave[meio + 1 + i];
        novo->ponteiro[i] = n->ponteiro[meio + 1 + i];
    }

    // Atualizar o número de chaves no nó original
    n->numChaves = meio;

    // Ajustar o pai
    if (pai == NULL) {
        noBMais *novoRaiz = criarNo(0);
        novoRaiz->chave[0] = chavePromovida;
        novoRaiz->ponteiro[0] = n;
        novoRaiz->ponteiro[1] = novo;
        novoRaiz->numChaves = 1;
        novo->pai = novoRaiz;
        n->pai = novoRaiz;
        pai = novoRaiz;
    } else {
        inserirChaveNo(pai, chavePromovida, novo);
        novo->pai = pai;
    }
}

// Função para inserir uma chave na árvore B+
void inserir(noBMais **raiz, int chave) {
    if (vazia(*raiz)) {
        *raiz = criarNo(1);
    }

    noBMais *n = *raiz;
    // Se a raiz está cheia, precisa ser dividida
    if (n->numChaves == ORDEM - 1) {
        dividirNo(n, NULL, 0);
    }

    // Inserir a chave no nó
    n = *raiz;
    inserirChaveNo(n, chave, NULL);
}

// Função para contar o número de folhas na árvore B+
int contarFolhas(noBMais *r) {
    if (vazia(r)) return 0;

    // Se for folha, retorna 1
    if (r->eh_folha) {
        return 1;
    }

    // Caso contrário, conta as folhas nos filhos
    int numFolhas = 0;
    for (int i = 0; i < r->numChaves + 1; i++) {
        numFolhas += contarFolhas((noBMais *)r->ponteiro[i]);
    }
    return numFolhas;
}

// Função para imprimir as chaves das folhas no intervalo [a, b]
void imprimeFolhasIntervalo(noBMais *r, int a, int b) {
    if (vazia(r)) return;

    // Se o nó for folha, verifica se as chaves estão dentro do intervalo
    if (r->eh_folha) {
        for (int i = 0; i < r->numChaves; i++) {
            if (r->chave[i] >= a && r->chave[i] <= b) {
                printf("%d ", r->chave[i]);
            }
        }
        return;
    }

    // Se não for folha, percorre as subárvores recursivamente
    for (int i = 0; i < r->numChaves && r->chave[i] <= b; i++) {
        if (r->chave[i] >= a) {
            // Imprime as folhas que estão no intervalo
            imprimeFolhasIntervalo((noBMais *)r->ponteiro[i], a, b);
        }
    }
}

// Função para imprimir a árvore (simplesmente para teste)
void imprimirArvore(noBMais *r) {
    if (vazia(r)) return;
    if (r->eh_folha) {
        for (int i = 0; i < r->numChaves; i++) {
            printf("%d ", r->chave[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i < r->numChaves + 1; i++) {
            imprimirArvore((noBMais *)r->ponteiro[i]);
        }
    }
}

int main() {
    noBMais *raiz = NULL;

    // Inserção de chaves para testar
    inserir(&raiz, 10);
    inserir(&raiz, 20);
    inserir(&raiz, 5);
    inserir(&raiz, 15);
    inserir(&raiz, 30);
    inserir(&raiz, 25);
    inserir(&raiz, 35);
    
    // Imprimir a árvore após inserções
    printf("Árvore B+ (in-ordem):\n");
    imprimirArvore(raiz);

    // Contar o número de folhas
    printf("\nNúmero de folhas: %d\n", contarFolhas(raiz));

    // Imprimir as chaves das folhas no intervalo [10, 30]
    printf("\nChaves no intervalo [10, 30]:\n");
    imprimeFolhasIntervalo(raiz, 10, 30);
    printf("\n");

    return 0;
}