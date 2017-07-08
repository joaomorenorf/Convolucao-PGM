#include <stdio.h>
#include <stdlib.h>
#include "PGM.h"
#include <string.h>


PGM *LerPGM (char* entrada) {
    // Abrir o arquivo
    FILE *imagem;
    imagem=fopen(entrada, "r");
    if (!imagem) {
        printf("Erro na abertura do arquivo.\n");
        exit (1);
    }
    char *c;
    c=(char *)malloc(3*sizeof(char));
    fscanf(imagem, "%s", c);
    c[2] = '\0';
    if (strcmp(c, "P2") != 0){
        printf("\nO Arquivo nao e PGM.\n");
    }
    free(c);

    // Iniciar PGM_Entrada
    PGM *PGM_Entrada=malloc(sizeof(PGM));
    fscanf (imagem, "%d", &PGM_Entrada->c);
    fscanf (imagem, "%d", &PGM_Entrada->l);
    fscanf (imagem, "%hhu", &PGM_Entrada->maximo);
    unsigned char **MatrizEntrada=(unsigned char **)malloc((PGM_Entrada->l+2)*sizeof(char *));
    int ii;
    for (ii=0; ii < PGM_Entrada->l+2; ii++) {
        MatrizEntrada[ii]=(unsigned char *)malloc((PGM_Entrada->c+2)*sizeof(char));
    }
    PGM_Entrada->imagem=MatrizEntrada;

    // Copiar imagem em PGM_Entrada.imagem
    int jj;
    for(ii=1; ii < PGM_Entrada->l+1; ii++) {
        for (jj=1; jj < PGM_Entrada->c+1; jj++) {
            if (fscanf(imagem,"%hhu", &PGM_Entrada->imagem[ii][jj]) != 1) {
                printf("\nErro ao copiar o centro da imagem.\n");
                exit (2);
            }
        }
    }
    // Copiar bordas PGM_Entrada.imagem
    for(ii=1; ii < PGM_Entrada->l+1; ii++) {
        PGM_Entrada->imagem[ii][0]=PGM_Entrada->imagem[ii][1];                             // Copiar a borda esquerda da imagem
    }
    for(ii=1; ii < PGM_Entrada->l+1; ii++) {
        PGM_Entrada->imagem[ii][PGM_Entrada->c+1]=PGM_Entrada->imagem[ii][PGM_Entrada->c]; // Copiar a borda direita  da imagem
    }
    for(ii=0; ii < PGM_Entrada->c+2; ii++) {
        PGM_Entrada->imagem[0][ii]=PGM_Entrada->imagem[1][ii];                             // Copiar a borda inferior da imagem
    }
    for(ii=0; ii < PGM_Entrada->c+2; ii++) {
        PGM_Entrada->imagem[PGM_Entrada->l+1][ii]=PGM_Entrada->imagem[PGM_Entrada->l][ii]; // Copiar a borda superior da imagem
    }
    fclose (imagem);
    return PGM_Entrada;
}

void SalvarPGM(PGM *PGM_Saida, char* saida) {
    // Criar arquivo de saída
    FILE *saidaf;
    saidaf=fopen(saida, "w");
    if (!saidaf) {
        printf("Erro na abertura do arquivo de saida.\n");
        exit (8);
    }
    fprintf(saidaf, "P2\n%d %d %d\n", PGM_Saida->c, PGM_Saida->l, PGM_Saida->maximo);

    // Copiar PGM_Saida->imagem no arquivo
    int ii, jj;
    for(ii=0; ii < PGM_Saida->l; ii++) {
        for (jj=0; jj < PGM_Saida->c; jj++) {
            fprintf(saidaf,"%d ", PGM_Saida->imagem[ii][jj]);
        }
        fprintf(saidaf,"\n");
    }
    // Desalocando saidaf e PGM_Saida
    fclose(saidaf);
    for (ii=0; ii < PGM_Saida->l; ii++) {
        free(PGM_Saida->imagem[ii]);
    }
    free(PGM_Saida->imagem);
    free(PGM_Saida);
}

void Convolucao(PGM *PGM_Entrada, char **kernel, PGM *PGM_Saida) {
    // Fazer a convolucao
    int jj, ii;
    for (ii=1; ii < PGM_Entrada->l+1; ii++) {
        for (jj=1; jj < PGM_Entrada->c+1; jj++) {
            int val =
            (int) PGM_Entrada->imagem[ii-1][jj-1]*kernel[2][2] + PGM_Entrada->imagem[ii-1][jj]*kernel[2][1] + PGM_Entrada->imagem[ii-1][jj+1]*kernel[2][0] +
                  PGM_Entrada->imagem[ii  ][jj-1]*kernel[1][2] + PGM_Entrada->imagem[ii  ][jj]*kernel[1][1] + PGM_Entrada->imagem[ii  ][jj+1]*kernel[1][0] +
                  PGM_Entrada->imagem[ii+1][jj-1]*kernel[0][2] + PGM_Entrada->imagem[ii+1][jj]*kernel[0][1] + PGM_Entrada->imagem[ii+1][jj+1]*kernel[0][0] ;
            if(val > 255) val = 255;
            else if(val < 0) val = 0;
            PGM_Saida->imagem[ii-1][jj-1] = val;
        }
    }
    // Desalocar PGM_Entrada e kernel
    for (ii=0; ii < PGM_Entrada->l+2; ii++) {
        free(PGM_Entrada->imagem[ii]);
    }
    free(PGM_Entrada->imagem);
    free(PGM_Entrada);
    for (ii=0; ii < 3; ii++) {
        free(kernel[ii]);
    }
    free(kernel);
}

PGM *IniciaPGM_Saida(PGM *PGM_Entrada) {
    // Iniciar PGM_Saida
    PGM *PGM_Saida=malloc(sizeof(PGM));
    PGM_Saida->c=PGM_Entrada->c;
    PGM_Saida->l=PGM_Entrada->l;
    PGM_Saida->maximo=PGM_Entrada->maximo;
    unsigned char **MatrizSaida=(unsigned char **)malloc(PGM_Saida->l*sizeof(char *));
    int ii;
    for (ii=0; ii < PGM_Entrada->l; ii++) {
        MatrizSaida[ii]=(unsigned char *)malloc(PGM_Entrada->c*sizeof(char));
    }
    PGM_Saida->imagem=MatrizSaida;
    return (PGM_Saida);
}
