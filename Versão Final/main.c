#include <stdio.h>
#include <stdlib.h>
#include "PGM.h"

int main (int argc, char *argv[]) {

    if (argc != 3) {
        printf ("Numero de argumentos invalido, espera-se 3, %d foram recebidos.", argc);
        exit(1);
    }

    PGM *PGM_Entrada=LerPGM(argv[1]);

    PGM *PGM_Saida=IniciaPGM_Saida(PGM_Entrada);

    // Salvar kernel
    char **kernel=(char **)malloc(3*sizeof(char *));
    int ii,jj;
    for (ii=0; ii < 3; ii++) {
        kernel[ii]=(char *)malloc(3*sizeof(char));
    }
    for(ii=0; ii < 3; ii++) {
        for (jj=0; jj < 3; jj++) {
            if (jj==0) kernel[ii][jj]=-1;
            else if (jj==1) kernel[ii][jj]=0;
            else if (jj==2) kernel[ii][jj]=1;
            else {
                printf("\nErro ao copiar o kernel.\n");
                exit (7);
            }

        }
    }

    Convolucao(PGM_Entrada, kernel, PGM_Saida);

    SalvarPGM(PGM_Saida, argv[2]);

    return 0;
}
