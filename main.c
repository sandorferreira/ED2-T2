// Trabalho 2
/* Informar nomes dos arquivos teste.txt e alfabeto.txt na linha de
comando */
/* Exemplo: a.out teste.txt alfabeto.txt
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXALFABETO 255
#define TRUE 1
#define FALSE 0
typedef short TipoAlfabeto[MAXALFABETO + 1];
FILE *ArqTxt, *ArqAlf;
TipoAlfabeto Alfabeto;
char Palavra[256];
char Linha[256];
int i;
short aux;

void DefineAlfabeto(short *Alfabeto) {
    char Simbolos[MAXALFABETO + 1];
    int i, CompSimbolos;
    char *TEMP;
    for (i = 0; i <= MAXALFABETO; i++)
        Alfabeto[i] = FALSE;
    fgets(Simbolos, MAXALFABETO + 1, ArqAlf);
    TEMP = strchr(Simbolos, '\n');
    if (TEMP != NULL) *TEMP = 0;
    CompSimbolos = strlen(Simbolos);
    for (i = 0; i < CompSimbolos; i++)
        Alfabeto[Simbolos[i] + 127] = TRUE;
    Alfabeto[0] = FALSE; /* caractere de codigo zero: separador */
}

int main(int argc, char *argv[]) {
    ArqTxt = fopen("Texto.txt", "r");
    ArqAlf = fopen("Alfabeto.txt", "r");
    DefineAlfabeto(Alfabeto);
    aux = FALSE;
    while (fgets(Linha, 256, ArqTxt) != NULL) { //ENQUANTO PEGAR LINHA DO LISTA
        for (i = 1; i <= strlen(Linha); i++) {
            if (Alfabeto[Linha[i - 1] + 127]) {
                sprintf(Palavra + strlen(Palavra), "%c", Linha[i - 1]);
                aux = TRUE;
            } else
                if (aux) {
                puts(Palavra);
                *Palavra = '\0';
                aux = FALSE;
            }
        }
    }
    if (aux) {
        puts(Palavra);
        *Palavra = '\0';
    }
    fclose(ArqTxt);
    fclose(ArqAlf);
    return 0;
}
/* End. */