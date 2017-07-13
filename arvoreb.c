#include <sys/time.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"arvoreb.h"
#define TRUE  1
#define FALSE 0
#define MAX 10

void EE(TipoApontadorArv *Ap) {
    TipoApontadorArv Ap1;
    Ap1 = (*Ap)->Esq;
    (*Ap)->Esq = Ap1->Dir;
    Ap1->Dir = *Ap;
    Ap1->BitE = Vertical;
    (*Ap)->BitE = Vertical;
    *Ap = Ap1;
}

void ED(TipoApontadorArv *Ap) {
    TipoApontadorArv Ap1, Ap2;
    Ap1 = (*Ap)->Esq;
    Ap2 = Ap1->Dir;
    Ap1->BitD = Vertical;
    (*Ap)->BitE = Vertical;
    Ap1->Dir = Ap2->Esq;
    Ap2->Esq = Ap1;
    (*Ap)->Esq = Ap2->Dir;
    Ap2->Dir = *Ap;
    *Ap = Ap2;
}

void DD(TipoApontadorArv *Ap) {
    TipoApontadorArv Ap1;
    Ap1 = (*Ap)->Dir;
    (*Ap)->Dir = Ap1->Esq;
    Ap1->Esq = *Ap;
    Ap1->BitD = Vertical;
    (*Ap)->BitD = Vertical;
    *Ap = Ap1;
}

void DE(TipoApontadorArv *Ap) {
    TipoApontadorArv Ap1, Ap2;
    Ap1 = (*Ap)->Dir;
    Ap2 = Ap1->Esq;
    Ap1->BitE = Vertical;
    (*Ap)->BitD = Vertical;
    Ap1->Esq = Ap2->Dir;
    Ap2->Dir = Ap1;
    (*Ap)->Dir = Ap2->Esq;
    Ap2->Esq = *Ap;
    *Ap = Ap2;
}

void IInsere(TipoRegistro x, TipoApontadorArv *Ap,
        TipoInclinacao *IAp, short *Fim) {
    if (*Ap == NULL) {
        *Ap = (TipoApontadorArv) malloc(sizeof (TipoNo));
        *IAp = Horizontal;
        (*Ap)->Reg = x;
        (*Ap)->BitE = Vertical;
        (*Ap)->BitD = Vertical;
        (*Ap)->Esq = NULL;
        (*Ap)->Dir = NULL;
        *Fim = FALSE;
        return;
    }
    if (x.Chave < (*Ap)->Reg.Chave) {
        IInsere(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
        if (*Fim) return;
        if ((*Ap)->BitE != Horizontal) {
            *Fim = TRUE;
            return;
        }
        if ((*Ap)->Esq->BitE == Horizontal) {
            EE(Ap);
            *IAp = Horizontal;
            return;
        }
        if ((*Ap)->Esq->BitD == Horizontal) {
            ED(Ap);
            *IAp = Horizontal;
        }
        return;
    }
    if (x.Chave <= (*Ap)->Reg.Chave) {
        printf("Erro: Chave ja esta na arvore\n");
        *Fim = TRUE;
        return;
    }
    IInsere(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
    if (*Fim) return;
    if ((*Ap)->BitD != Horizontal) {
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->Dir->BitD == Horizontal) {
        DD(Ap);
        *IAp = Horizontal;
        return;
    }
    if ((*Ap)->Dir->BitE == Horizontal) {
        DE(Ap);
        *IAp = Horizontal;
    }
}

void InsereArv(TipoRegistro x, TipoApontadorArv *Ap) {
    short Fim;
    TipoInclinacao IAp;
    IInsere(x, Ap, &IAp, &Fim);
}

void Inicializa(TipoApontadorArv *Dicionario) {
    *Dicionario = NULL;
}

void EsqCurto(TipoApontadorArv *Ap, short *Fim) { /* Folha esquerda retirada => arvore curta na altura esquerda */
    TipoApontadorArv Ap1;
    if ((*Ap)->BitE == Horizontal) {
        (*Ap)->BitE = Vertical;
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->BitD == Horizontal) {
        Ap1 = (*Ap)->Dir;
        (*Ap)->Dir = Ap1->Esq;
        Ap1->Esq = *Ap;
        *Ap = Ap1;
        if ((*Ap)->Esq->Dir->BitE == Horizontal) {
            DE(&(*Ap)->Esq);
            (*Ap)->BitE = Horizontal;
        } else if ((*Ap)->Esq->Dir->BitD == Horizontal) {
            DD(&(*Ap)->Esq);
            (*Ap)->BitE = Horizontal;
        }
        *Fim = TRUE;
        return;
    }
    (*Ap)->BitD = Horizontal;
    if ((*Ap)->Dir->BitE == Horizontal) {
        DE(Ap);
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->Dir->BitD == Horizontal) {
        DD(Ap);
        *Fim = TRUE;
    }
}

void DirCurto(TipoApontadorArv *Ap, short *Fim) { /* Folha direita retirada => arvore curta na altura direita */
    TipoApontadorArv Ap1;
    if ((*Ap)->BitD == Horizontal) {
        (*Ap)->BitD = Vertical;
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->BitE == Horizontal) {
        Ap1 = (*Ap)->Esq;
        (*Ap)->Esq = Ap1->Dir;
        Ap1->Dir = *Ap;
        *Ap = Ap1;
        if ((*Ap)->Dir->Esq->BitD == Horizontal) {
            ED(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        } else if ((*Ap)->Dir->Esq->BitE == Horizontal) {
            EE(&(*Ap)->Dir);
            (*Ap)->BitD = Horizontal;
        }
        *Fim = TRUE;
        return;
    }
    (*Ap)->BitE = Horizontal;
    if ((*Ap)->Esq->BitD == Horizontal) {
        ED(Ap);
        *Fim = TRUE;
        return;
    }
    if ((*Ap)->Esq->BitE == Horizontal) {
        EE(Ap);
        *Fim = TRUE;
    }
}

void Antecessor(TipoApontadorArv q, TipoApontadorArv *r, short *Fim) {
    if ((*r)->Dir != NULL) {
        Antecessor(q, &(*r)->Dir, Fim);
        if (!*Fim) DirCurto(r, Fim);
        return;
    }
    q->Reg = (*r)->Reg;
    q = *r;
    *r = (*r)->Esq;
    free(q);
    if (*r != NULL) *Fim = TRUE;
}

void IRetira(TipoRegistro x, TipoApontadorArv *Ap, short *Fim) {
    TipoNo *Aux;
    if (*Ap == NULL) {
        printf("Chave nao esta na arvore\n");
        *Fim = TRUE;
        return;
    }
    if (x.Chave < (*Ap)->Reg.Chave) {
        IRetira(x, &(*Ap)->Esq, Fim);
        if (!*Fim) EsqCurto(Ap, Fim);
        return;
    }
    if (x.Chave > (*Ap)->Reg.Chave) {
        IRetira(x, &(*Ap)->Dir, Fim);
        if (!*Fim) DirCurto(Ap, Fim);
        return;
    }
    *Fim = FALSE;
    Aux = *Ap;
    if (Aux->Dir == NULL) {
        *Ap = Aux->Esq;
        free(Aux);
        if (*Ap != NULL) *Fim = TRUE;
        return;
    }
    if (Aux->Esq == NULL) {
        *Ap = Aux->Dir;
        free(Aux);
        if (*Ap != NULL) *Fim = TRUE;
        return;
    }
    Antecessor(Aux, &Aux->Esq, Fim);
    if (!*Fim) EsqCurto(Ap, Fim); /* Encontrou chave */
}

void Retira(TipoRegistro x, TipoApontadorArv *Ap) {
    short Fim;
    IRetira(x, Ap, &Fim);
}

void PesquisaArv(TipoRegistro *x, TipoApontadorArv *p) {
    if (*p == NULL) {
        printf("Erro: Registro nao esta presente na arvore\n");
        return;
    }
    if (x->Chave < (*p)->Reg.Chave) {
        PesquisaArv(x, &(*p)->Esq);
        return;
    }
    if (x->Chave > (*p)->Reg.Chave)
        PesquisaArv(x, &(*p)->Dir);
    else
        *x = (*p)->Reg;
}

void Testa1(TipoApontadorArv p, int nivel, int *NivelFolhas, short *PrimeiraFolha) {
    if (p == NULL)
        return;
    if (*PrimeiraFolha)
        if (*NivelFolhas < nivel) *NivelFolhas = nivel;
    if (p->Esq == NULL && p->Dir == NULL) {
        if (*PrimeiraFolha == TRUE)
            *PrimeiraFolha = FALSE;
        else {
            if (nivel != *NivelFolhas) {
                printf("Erro: Folhas em niveis diferentes\n");
                exit(1);
            }
        }
    }
    if (p->BitE == Horizontal)
        Testa1(p->Esq, nivel, NivelFolhas, PrimeiraFolha);
    else
        Testa1(p->Esq, nivel + 1, NivelFolhas, PrimeiraFolha);
    if (p->BitD == Horizontal)
        Testa1(p->Dir, nivel, NivelFolhas, PrimeiraFolha);
    else
        Testa1(p->Dir, nivel + 1, NivelFolhas, PrimeiraFolha);
}

void Testa2(TipoApontadorArv p, int *NivelFolhas, short *PrimeiraFolha) {
    if (p == NULL)
        return;
    if (p->Esq != NULL) {
        if (p->Reg.Chave < p->Esq->Reg.Chave) {
            //            printf("Erro: %d < que filho a esquerda \n", p->Reg.Chave);
            exit(1);
        }
        Testa2(p->Esq, NivelFolhas, PrimeiraFolha);
    }
    if (p->Dir == NULL)
        return;
    if (p->Reg.Chave > p->Dir->Reg.Chave) {
        //        printf("Erro: %d > que filho a direita \n", p->Reg.Chave);
        exit(1);
    }
    Testa2(p->Dir, NivelFolhas, PrimeiraFolha);
}

void Testa(TipoApontadorArv Arvore) {
    int NivelFolhas = 0;
    short PrimeiraFolha = TRUE;
    Testa1(Arvore, 1, &NivelFolhas, &PrimeiraFolha);
    Testa2(Arvore, &NivelFolhas, &PrimeiraFolha);
}

double rand0a1() {
    double resultado = (double) rand() / RAND_MAX; /* Dividir pelo maior inteiro */
    if (resultado > 1.0) resultado = 1.0;
    return resultado;
}

void Permut(int *A, int n) { /* Obtem permutacao randomica dos numeros entre 1 e n */
    int i, j, b;
    for (i = n; i >= 1; i--) {
        j = (int) (i * rand0a1() + 1);
        b = A[i - 1];
        A[i - 1] = A[j - 1];
        A[j - 1] = b;
    }
}

TipoRegistro* criaRegistro(char *Palavra) {
    TipoRegistro *novo = (TipoRegistro*) malloc(sizeof (TipoRegistro));
    for (int i = 0; i < strlen(Palavra); i++) {
        novo->Chave[i] = Palavra[i];
    }
    novo->repeticao = NULL;
    return novo;
}

void imprimeArvore(TipoApontadorArv Arvore) {
    if(Arvore->Esq != NULL)
        imprimeArvore(Arvore->Esq);
    printf("%s\n",Arvore->Reg.Chave);
    if(Arvore->Dir != NULL)
        imprimeArvore(Arvore->Dir);
}

void imprimeArv2(TipoApontadorArv Arvore, FILE* ArqSaida) {
    fprintf(ArqSaida, "%s", Arvore->Reg.Chave);
    if (Arvore->Reg.repeticao != NULL) {
        TipoRepeticao *aux = Arvore->Reg.repeticao;
        while (aux != NULL) {
            fprintf(ArqSaida, " %d", aux->linha);
            aux = aux->proximo;
        }
        fprintf(ArqSaida, "\n");
    }
}

void imprimeArv(TipoApontadorArv Arvore, FILE* ArqSaida) {
    if (Arvore->Esq != NULL)
        imprimeArv(Arvore->Esq,ArqSaida);
    imprimeArv2(Arvore, ArqSaida);
    if (Arvore->Dir != NULL)
        imprimeArv(Arvore->Dir,ArqSaida);
}

TipoRegistro* pesquisaArv(TipoApontadorArv Arvore, char* palavra) {
    TipoRegistro* aux = NULL;
    if ((strcmp(Arvore->Reg.Chave,palavra) == 0) && aux == 0) {
        aux = &Arvore->Reg;
        return aux;
    } else {
        if (Arvore->Esq != NULL) {
            aux = pesquisaArv(Arvore->Esq, palavra);
            if (aux != NULL) {
                return aux;
            }
        }
        if (Arvore->Dir != NULL) {
            aux = pesquisaArv(Arvore->Dir, palavra);
        }
        return aux;
    }
}

void criaRepeticaoArv(int nLinha, TipoApontadorArv Arvore) {
    TipoRepeticao *novo = (TipoRepeticao*) malloc(sizeof (TipoRepeticao));
    novo->linha = nLinha;
    novo->proximo = NULL;
    TipoRepeticao *aux = Arvore->Reg.repeticao;
    if (aux != NULL) {
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        if (aux->linha == nLinha) {
            return;
        } else {
            aux->proximo = novo;
        }
    } else {
        Arvore->Reg.repeticao = novo;
    }
}

short adicionaLinhaArv(char *Palavra, int nLinha, TipoApontadorArv Arvore) {
    short achou = FALSE;
    if (strcmp(Arvore->Reg.Chave, Palavra) == 0) {
        criaRepeticaoArv(nLinha, Arvore);
        return TRUE;
    }
    if (Arvore->Esq != NULL) {
        achou = adicionaLinhaArv(Palavra, nLinha, Arvore->Esq);
        if (achou == TRUE) {
            return achou;
        }
    }

    if (Arvore->Dir != NULL) {
        achou = adicionaLinhaArv(Palavra, nLinha, Arvore->Dir);
        if (achou == TRUE) {
            return achou;
        }
    }
}

int procuraLinhaArv (int linha, TipoChave palavra, TipoApontadorArv arvore){
    TipoRegistro* reg = pesquisaArv(arvore, palavra);
    TipoRepeticao* rep = reg->repeticao;
    while (rep != NULL){
        if (rep->linha == linha){
            return 1;
        }
        rep = rep->proximo;
    }
    return 0;
}

TipoApontadorArv criaArvore(FILE* indice) {
    TipoApontadorArv Dicionario;
    char Palavra[256];
    char Linha[256];
    TipoRegistro x;
    int i, j, k, n, aux = 0;
    Inicializa(&Dicionario);

    while (fgets(Linha, 256, indice) != NULL) {
        for (i = 0; i < strlen(Linha) - 1; i++) {
            Palavra[i] = Linha[i];
        }
        TipoRegistro *novo = criaRegistro(Palavra);
        memset(Palavra, 0, sizeof (Palavra));
        InsereArv(*novo, &Dicionario);
    }
    Testa(Dicionario);
    //    imprimeArv(Dicionario);
    return Dicionario;
}