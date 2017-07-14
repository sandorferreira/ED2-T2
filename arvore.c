#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>
#include "arvore.h"

#define MAX  1000
typedef char stringPalavra[256];


void PesquisaArv(TipoRegistro *x, TipoApontador *p)
{ if (*p == NULL) 
  { printf("Erro: Registro nao esta presente na arvore\n");
    return;
  }
  if (x->Chave < (*p)->Reg.Chave) 
  { PesquisaArv(x, &(*p)->Esq);
    return;
  }
  if (x->Chave > (*p)->Reg.Chave)
  PesquisaArv(x, &(*p)->Dir);
  else *x = (*p)->Reg;
} 

TipoRegistro* pesquisaArv(TipoNo* Arvore, char* palavra) {
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

int procuraLinhaArv (int linha, TipoChave palavra, TipoNo* arvore){
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

void Insere(TipoRegistro x, TipoApontador *p)
{ if (*p == NULL) 
  { *p = (TipoApontador)malloc(sizeof(TipoNo));
    (*p)->Reg = x;
    (*p)->Esq = NULL; 
    (*p)->Dir = NULL;
    return;
  }
  if (strcmp(x.Chave, (*p)->Reg.Chave) < 0) 
  { Insere(x, &(*p)->Esq); 
    return; 
  }
  if (strcmp(x.Chave ,(*p)->Reg.Chave) > 0)
  Insere(x, &(*p)->Dir);
  else printf("Erro : Registro ja existe na arvore\n");
} 

// if (x.Chave > (*p)->Reg.Chave)

void Inicializa(TipoApontador *Dicionario)
{ *Dicionario = NULL; }

void Antecessor(TipoApontador q, TipoApontador *r)
{ if ((*r)->Dir != NULL) 
  { Antecessor(q, &(*r)->Dir);
    return;
  }
  q->Reg = (*r)->Reg;
  q = *r; 
  *r = (*r)->Esq;
  free(q);
} 

void Retira(TipoRegistro x, TipoApontador *p)
{  TipoApontador Aux;
  if (*p == NULL) 
  { printf("Erro : Registro nao esta na arvore\n");
    return;
  }
  if (x.Chave < (*p)->Reg.Chave) { Retira(x, &(*p)->Esq); return; }
  if (x.Chave > (*p)->Reg.Chave) { Retira(x, &(*p)->Dir); return; }
  if ((*p)->Dir == NULL) 
  { Aux = *p;  *p = (*p)->Esq;
    free(Aux);
    return;
  }
  if ((*p)->Esq != NULL) 
  { Antecessor(*p, &(*p)->Esq);
    return;
  }
  Aux = *p;  *p = (*p)->Dir;
  free(Aux);
}  

void Central(TipoApontador p)
{ if (p == NULL) return;
  Central(p->Esq);
  puts(p->Reg.Chave);
  Central(p->Dir);
} 

void TestaI(TipoNo *p, char* pai)
{ if (p == NULL) return;
  if (p->Esq != NULL) 
  { if (strcmp(p->Reg.Chave, p->Esq->Reg.Chave) < 0 )
    { printf("Erro: Pai %s menor que filho a esquerda %s\n", p->Reg.Chave, 
             p->Esq->Reg.Chave);
      exit(1);
    }
  }
  if (p->Dir != NULL) 
  { if (strcmp(p->Reg.Chave, p->Dir->Reg.Chave) > 0 ) 
    { printf("Erro: Pai %s maior que filho a direita %s\n",  p->Reg.Chave, 
             p->Dir->Reg.Chave);
    exit(1);
    }
  }
  TestaI(p->Esq, p->Reg.Chave);
  TestaI(p->Dir, p->Reg.Chave);
}


void Testa(TipoNo *p)
{ if (p != NULL)
  TestaI(p, p->Reg.Chave);
}

double rand0a1() {
  double resultado=  (double) rand()/ RAND_MAX; /* Dividir pelo maior inteiro */
  if(resultado>1.0) resultado = 1.0;
  return resultado;
}

void Permut( int A[], int n) {
  int i,j; int b;
  for(i = n; i>0; i --) 
    { j = (i * rand0a1());
      b = A[i];
      A[i] = A[j];
      A[j] = b;
    }
}

void imprimeNo(TipoNo* Arvore) {
    printf("%s", Arvore->Reg.Chave);
    if (Arvore->Reg.repeticao != NULL) {
        TipoRepeticao *aux = Arvore->Reg.repeticao;
        while (aux != NULL) {
            printf(" %d", aux->linha);
            aux = aux->proximo;
        }
        printf("\n");
    }
}

void imprimeArvore(TipoNo* arv) {
  if (arv != NULL) { 
  imprimeArvore(arv->Esq);
  imprimeNo(arv);
  imprimeArvore(arv->Dir);
  }
}

TipoNo* criaArvore() {

  FILE* ArqPalavras = fopen("Palavras_Chave.txt", "r");
  TipoNo* arvore;// = NULL;
  int nPalavras = 0;
  char Linha[256];

  while(fgets(Linha, 256, ArqPalavras) != NULL) {
    nPalavras++;
  }

  fclose(ArqPalavras);

  ArqPalavras = fopen("Palavras_Chave.txt", "r");
  printf("%d\n", nPalavras);
  stringPalavra vetorPalavras[nPalavras];

  int iterator = 0;
  Inicializa(&arvore);
  while(fgets(vetorPalavras[iterator], 256, ArqPalavras)) {
        iterator++;
  }

  int vetorIndices[nPalavras];
  for (i = 0; i < nPalavras; i++) {
    vetorIndices[i] = i;
  }

  // PERMUTANDO PARA ÁRVORE NÃO VIRAR UMA LISTA ENCADEADA
  Permut(vetorIndices, nPalavras-1);

  for (int j=0;j<nPalavras;j++){
      for(int y=0; y<256;y++){
          if(vetorPalavras[j][y] == '\n')
              vetorPalavras[j][y] = 0;
      }
//      puts(vetorPalavras[j]);
  }
  
  for(int i = 0; i < nPalavras; i ++) {
    TipoRegistro novo;
    novo.Chave = vetorPalavras[vetorIndices[i]];
    novo.repeticao = NULL;
    Insere(novo, &arvore);
    Testa(arvore);
  }
  //imprimeArvore(arvore);
  //arvAux = arvore;

  return arvore;
}

void criaRepeticaoArv(int nLinha, TipoNo* Arvore) {
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

short adicionaLinhaArv(char *Palavra, int nLinha, TipoNo* Arvore) {
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

