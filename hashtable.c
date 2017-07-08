#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#define M  1000
#define N  50   /* Tamanho da chave */

int j, i;

void GeraPesos(TipoPesos p) { /* -Gera valores randomicos entre 1 e 10.000- */
    int i;
    struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    gettimeofday(&semente, NULL);
    srand((int) (semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = 0; i < N; i++)
        p[i] = 1 + (int) (10000.0 * rand() / (RAND_MAX + 1.0));
}

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

void criaHash(FILE* indice, TipoDicionario T) {
    InicializaHash(T);
    char Palavra[256], Linha[256];
    while (fgets(Linha, 256, indice) != NULL) {
        for (i = 0; i < strlen(Linha) - 1; i++) {
            Palavra[i] = Linha[i];
        }
        InsereHash(Palavra, T);
        memset(Palavra, 0, sizeof (Palavra));
    }
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

void novaPalavraHash(TipoChaveHash Chave, TipoDicionario T, int pos) {
    TipoItem *novo = (TipoItem*) malloc(sizeof (TipoItem));
    strcpy(novo->Chave, Chave);
    novo->repeticao = NULL;
    T[pos] = novo;
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
        aux->proximo = novo;
        return;
    } else {
        T[pos]->repeticao = novo;
    }
}

void RetiraHash(TipoChaveHash Ch, TipoPesos p, TipoDicionario T) {
    TipoIndice i;
    i = Pesquisa(Ch, T);
    if (i < M) {
    } else printf("Registro nao esta presente\n");
}

void ImprimeHash(TipoDicionario tabela) {
    int i, j, tam;
    for (i = 0; i < M; i++) {
        printf("%d  ", i);
        if (tabela[i] != NULL) {
            tam = strlen(tabela[i]->Chave);
            for (j = 0; j < tam; j++)
                putchar(tabela[i]->Chave[j]);
            imprimeLinhas(tabela, i);
            putchar('\n');
        }
    }
} /* Imprime */

void imprimeLinhas(TipoDicionario T, int i) {
    TipoRepeticaoHash* aux = T[i]->repeticao;
    while (aux != NULL) {
        printf(" %d", aux->linha);
        aux = aux->proximo;
    }
}

void LerPalavraHash(char *p, int Tam) {
    char c;
    int i, j;
    fflush(stdin);
    j = 0;
    while (((c = getchar()) != '\n') && (j < (Tam - 1))) p[j++] = c;
    p[j] = '\0';
    while (c != '\n') c = getchar();
    /* Desconsiderar espacos ao final da cadeia como ocorre no Pascal.*/
    for (i = j - 1; (i >= 0 && p[i] == ' '); i--) p[i] = '\0';
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