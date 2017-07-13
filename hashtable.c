#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#define M  1000
#define N  50   /* Tamanho da chave */

int j, i;

TipoIndice h(TipoChaveHash Chave) {
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++)
        Soma += (unsigned int) Chave[i];
    Soma *= comp;
    return (Soma % M);
}

void InicializaHash(TipoDicionario T) {
    int i;
    for (i = 0; i < M; i++) T[i] = NULL;
}

TipoApontadorHash Pesquisa(TipoChaveHash Ch, TipoDicionario T) {
    unsigned int i = 0;
    unsigned int Inicial;
    Inicial = h(Ch);
    if (T[(Inicial + i) % M] != NULL) {
        while ((T[(Inicial + i) % M] != NULL) && (strcmp(T[(Inicial + i) % M]->Chave, Ch) != 0) && i < M)
            i++;
        if ((T[(Inicial + i) % M] == NULL)) {
            return M;
        }
        if (strcmp(T[(Inicial + i) % M]->Chave, Ch) == 0)
            return ((Inicial + i) % M);
        else return M; /* Pesquisa sem sucesso */
    }
}

void InsereHash(TipoChaveHash x, TipoDicionario T) {
    unsigned int i = 0;
    unsigned int Inicial;
    Inicial = h(x);
    while (T[(Inicial + i) % M] != NULL && (i < M))
        i++;
    if (i < M) {
        novaPalavraHash(x, T, (Inicial + i) % M);
    } else printf("Está cheio?!\n");
}

void novaPalavraHash(TipoChaveHash Chave, TipoDicionario T, int aux) {
    TipoItem *novo = (TipoItem*) malloc(sizeof (TipoItem));
    strcpy(novo->Chave, Chave);
    novo->repeticao = NULL;
    T[aux] = novo;
}

void checaPalavraHash(TipoDicionario T, TipoChaveHash x, int nLinha) {
    int aux = Pesquisa(x, T);
    if (aux < M) {
        adicionaLinhaHash(T, aux, nLinha);
        return;
    }
}

void adicionaLinhaHash(TipoDicionario T, int pos, int nLinha) {
    TipoRepeticaoHash* novo = (TipoRepeticaoHash*) malloc(sizeof (TipoRepeticaoHash));
    novo->linha = nLinha;
    novo->proximo = NULL;
    if (T[pos]->repeticao != NULL) {
        TipoRepeticaoHash* aux = T[pos]->repeticao;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        if (aux->linha == nLinha) {
            return;
        } else {
            aux->proximo = novo;
            return;
        }
    } else {
        T[pos]->repeticao = novo;
    }
}

void imprimeLinhas(TipoDicionario T, int i, FILE* ArqSaida) {
    TipoRepeticaoHash* aux = T[i]->repeticao;
    while (aux != NULL) {
        fprintf(ArqSaida, " %d", aux->linha);
        aux = aux->proximo;
    }
    fprintf(ArqSaida, "\n");
}

int procuraLinhaHash(int linha, TipoChaveHash palavra, TipoDicionario T) {
    TipoApontadorHash ap = Pesquisa(palavra, T);
    TipoRepeticaoHash* aux = T[ap]->repeticao;
    while (aux != NULL) {
        if (aux->linha == linha) {
            return 1;
        }
        aux = aux->proximo;
    }
    return 0;
}

void criaRepeticaoHash(int nLinha, TipoItem Item) {
    TipoRepeticaoHash* novo = (TipoRepeticaoHash*) malloc(sizeof (TipoRepeticaoHash));
    novo->linha = nLinha;
    novo->proximo = NULL;
    TipoRepeticaoHash *aux = Item.repeticao;
    if (aux != NULL) {
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    } else {
        Item.repeticao = novo;
    }
}

void imprimeHash(TipoApontadorHash apontador, TipoDicionario T, FILE* Saida) {
    int tam = strlen(T[apontador]->Chave);
    for (int j = 0; j < tam; j++)
        putc(T[apontador]->Chave[j], Saida);
    imprimeLinhas(T, apontador, Saida);
}