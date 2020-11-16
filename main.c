#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int chave;
    int altura;
    struct No * esq;
    struct No * dir;
} No;

typedef No * Arvore;

int max(int, int);
int encontrarAltura(Arvore);
int diferencaAltura(No *);
void preOrder(Arvore);
No * criarNoVazio(int);
No * noMenorValor(No *p);
No * rotacionarDireita(No *);
No * rotacionarEsquerda(No *);
Arvore inserir(Arvore, int);
Arvore remover(Arvore, int);

int max(int a, int b){
    return (a > b)? a : b;
}

int encontrarAltura(Arvore ap){
    if (ap == NULL)
        return 0;
    return ap->altura;
}

int diferencaAltura(No *p){
    if (p == NULL)
        return 0;
    return encontrarAltura(p->esq) - encontrarAltura(p->dir);
}

void preOrder(Arvore ap){
    if(ap != NULL){
        printf("%d ", ap->chave);
        preOrder(ap->esq);
        preOrder(ap->dir);
    }
}

No * criarNoVazio(int chave){
    No * novo = malloc(sizeof(No));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;

    return novo;
}

No * noMenorValor(No *p){
    No* atual = p;

    while (atual->esq != NULL)
        atual = atual->esq;

    return atual;
}

No * rotacionarDireita(No* p){
    No *x = p->esq;
    No *T2 = x->dir;

    x->dir = p;
    p->esq = T2;

    p->altura = max(encontrarAltura(p->esq), encontrarAltura(p->dir)) + 1;
    x->altura = max(encontrarAltura(x->esq), encontrarAltura(x->dir)) + 1;

    return x;
}

No * rotacionarEsquerda(No* p){
    No *y = p->dir;
    No *T2 = y->esq;

    y->esq = p;
    p->dir = T2;

    p->altura = max(encontrarAltura(p->esq), encontrarAltura(p->dir)) + 1;
    y->altura = max(encontrarAltura(y->esq), encontrarAltura(y->dir)) + 1;

    return y;
}

Arvore inserir(Arvore ap, int chave){
    if (ap == NULL)
        return(criarNoVazio(chave));

    if (chave < ap->chave)
        ap->esq = inserir(ap->esq, chave);
    else if (chave > ap->chave)
        ap->dir = inserir(ap->dir, chave);
    else
        return ap;

    ap->altura = 1 + max(encontrarAltura(ap->esq), encontrarAltura(ap->dir));

    int diferenca = diferencaAltura(ap);

    if (diferenca > 1 && chave < ap->esq->chave)
        return rotacionarDireita(ap);

    if (diferenca < -1 && chave > ap->dir->chave)
        return rotacionarEsquerda(ap);

    if (diferenca > 1 && chave > ap->esq->chave){
        ap->esq = rotacionarEsquerda(ap->esq);
        return rotacionarDireita(ap);
    }

    if (diferenca < -1 && chave < ap->dir->chave){
        ap->dir = rotacionarDireita(ap->dir);
        return rotacionarEsquerda(ap);
    }

    return ap;
}

Arvore remover(Arvore ap , int chave){
    if (ap == NULL)
        return ap;

    if ( chave < ap->chave )
        ap->esq = remover(ap->esq, chave);
    else if( chave > ap->chave )
        ap->dir = remover(ap->dir, chave);
    else{
        if((ap->esq == NULL) || (ap->dir == NULL)){
            No *temp = ap->esq ? ap->esq : ap->dir;

            if (temp == NULL){
                temp = ap;
                ap = NULL;
            }
            else
                *ap = *temp;

            free(temp);
        }
        else{
            No* temp = noMenorValor(ap->dir);

            ap->chave = temp->chave;

            ap->dir = remover(ap->dir, temp->chave);
        }
    }

    if (ap == NULL)
        return ap;

    ap->altura = 1 + max(encontrarAltura(ap->esq), encontrarAltura(ap->dir));

    int diferenca = diferencaAltura(ap);

    if (diferenca > 1 && diferencaAltura(ap->esq) >= 0)
        return rotacionarDireita(ap);

    if (diferenca > 1 && diferencaAltura(ap->esq) < 0){
        ap->esq = rotacionarEsquerda(ap->esq);
        return rotacionarDireita(ap);
    }

    if (diferenca < -1 && diferencaAltura(ap->dir) <= 0)
        return rotacionarEsquerda(ap);

    if (diferenca < -1 && diferencaAltura(ap->dir) > 0){
        ap->dir = rotacionarDireita(ap->dir);
        return rotacionarEsquerda(ap);
    }

    return ap;
}

int main(){
    Arvore raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);


    printf("A árvore AVL em pre-ordem é: \n");
    preOrder(raiz);

    raiz = remover(raiz, 50);
    raiz = remover(raiz, 25);
    raiz = remover(raiz, 40);

    printf("A árvore AVL em pre-ordem é: \n");
    preOrder(raiz);

    return 0;
}
