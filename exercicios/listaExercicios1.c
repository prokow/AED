#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Função recursiva que receba um número inteiro n e imprima todos os inteiros entre 0 e N em ordem decrescente
void ordem_decrescente(int n){
    if(n < 0){
        return;
    }else{
        printf("%d ", n);
        ordem_decrescente(n-1);
    }
}

//Função recursiva que receba um número inteiro n e imprima todos os inteiros entre 0 e N em ordem crescente
void ordem_crescente(int n){
    if(n < 0){
        return;
    }else{
        ordem_crescente(n - 1); //será feito do n até quando for n<0, quando chegar no -1 será feitos as impressões
        printf("%d ", n);
    }
}

//Funç˜ao recursiva que receba um numero inteiro n e calcule o somatorio dos numeros entre 0 e n
int soma(int n){
    if(n<0){
        return 0;
    }else{
        return n + soma(n-1);
    }
}

//função auxiliar para o superfatorial
int fatorial(int n){
    if(n==0){
        return 1;
    }else
        return n * fatorial(n-1);
}

//Função recursiva que receba um numero inteiro n e calcule seu superfatorial (sf), onde o superfatorial
//de n é o produtos dos n primeiros fatoriais. Assim, por exemplo sf(5) = 1! × 2! × 3! × 4! × 5! = 34.560
int superfatorial(int n){
    if(n==0){
        return 1;
    }else
        return fatorial(n) * superfatorial(n-1);
}


//Função recursiva para calcular o fatorial exponencial de um inteiro n, calculado segundo a formula: fatexp(n) = n^(n−1)^(n−2)...
int fatorial_exponencial(int n){
    if(n==0){
        return 1;
    }else
        return pow(n, fatorial_exponencial(n-1));

}

//Função recursiva para calcular o n-ésimo numero catal˜ao
float numeroCatalao(float n){
    if(n==0){
        return 1;
    }else if(n>0)
        return ((4*n - 2)/(n+ 1)) * numeroCatalao(n-1);

}


//um algoritmo recursivo que dada uma cadeia de caracteres str, decida se str ´e pal´ındrome ou n˜ao.
void palindrome(char* str){

}

//Projete um algoritmo recursivo que inverta a ordem dos elementos de um vetor
int invertaVetor(int v[], int n){
    if(n==0){
        return v[0];
    }else {
        int x = v[n];
        invertaVetor(v,n-1);
        return x;
    }
}

void imprimeVetor(int v[], int n){
    for(int i =0; i<n; i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}

//função recursiva para calcuar a função de Ackerman
//A(m,n) = n+1 se m =0
//A(m,n) = A(m - 1, 1) se m>0 e n=0
//A(m,n) = A(m - 1, A(m, n - 1))  se m>0 e n>0
int ackerman(int m, int n){
    if(m == 0){
        return n + 1;
    }else{
    if(m > 0 && n == 0){
        return ackerman(m-1,1);
    } else if(m > 0 && n > 0){
        return ackerman(m - 1,ackerman(m, n - 1));
        }
    }
}

//função recursiva que receba um numero inteiro n e calcule a soma dos digitos de n
//Ex: n = 327 --> 3+2+7 = 12
int somaNumeroInteiro(int n){
    if(n == 0){
        return 0;
    }else
        printf("%d\n",n);
        return n%10 + somaNumeroInteiro(n/10);
}


int main(){

//---------------------1----------------------
//ordem_crescente(5);
printf("\n");

//---------------------2----------------------
//ordem_decrescente(5);

int x,y;
    //printf("-Digite um numero: ");
    //scanf("%d",&x);
    //scanf("%d",&y);

    //---------------------3----------------------
    //printf("SOMA = %d\n",soma(x));

    //---------------------4----------------------
    //printf("Fatorial de %d! = %d\n",x, fatorial(x));
    //printf("sf(%d) = %d\n", x, superfatorial(x));

    //---------------------5----------------------
    //printf("fatexp(%d) = %d", x, fatorial_exponencial(x));

    //---------------------6----------------------
    //printf("numero Catalao C(%d) = %.1f", x, numeroCatalao(x));


    //---------------------9----------------------
    int v[5] = {0,1,2,4,5};
    invertaVetor(v,5);
    imprimeVetor(v,5);

    //---------------------10----------------------
    //int ackermanResult = ackerman(x,y);
    //printf("A(%d,%d) = %d\n", x, y, ackermanResult);


    //---------------------11----------------------
    //int x = somaNumeroInteiro(y);
    //printf("\n%d = %d\n",y,x);

    //---------------------12----------------------
    /*
    int func(int n){
        if(n == 0)
            return 1;
        if(n == 1)
            return 1;
        if(n == 2){
            return 2;
        else
            return func(func(n-1)) + func(n-2);
        }
    }

    func(2) = 2
    func(3) = 3
    func(5) = 5
    */


    return 0;
}
