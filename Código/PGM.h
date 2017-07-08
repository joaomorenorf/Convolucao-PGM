#ifndef PGM_INCLUDED
#define PGM_INCLUDED

typedef struct {
    int c;                          // número de colunas na imagem
    int l;                          // número de linhas na imagem
    unsigned char maximo;           // valor máximo para cada pixelconvolucao
    unsigned char **imagem;         // variável para armazenar os pixels da imagem (matriz)
} PGM;

typedef struct {
    int **e;
} TipoKernel;

PGM *LerPGM(char* entrada);

/*--------------------------------------------------------------------------------
Protótipo: PGM *LerPGM(char* entrada)
Função: Lê o arquivo de entrada e armazena ele na estrutura de dados
Entrada: Vetor endereço do arquivo
Saida: Tipo abstrato de dados do tiopo imagem PGM
--------------------------------------------------------------------------------*/

void SalvarPGM(PGM *img, char* saida);

/*--------------------------------------------------------------------------------
Protótipo: void SalvarPGM(PGM *img, char* saida)
Função: Lê a estrutura de dados e salva como arquivo .pgm
Entrada: Tipo abstrato de dados do tipo imagem PGM e vetor endereço do arquivo
Saida: Sem saída da função, mas salva um arquivo no endereço dado
--------------------------------------------------------------------------------*/

void Convolucao(PGM *img, char **kernel, PGM *saida);

/*--------------------------------------------------------------------------------
Protótipo: void Convolucao(PGM *img, char **kernel, PGM *saida)
Função: Executa a operação de convolução na imagem
Entrada: Tipo abstrato de dados do tipo imagem de entrada e saida da operação e a matriz kernel
Saida: A função não retorna saida, mas processa os valores da TAD PGM saída
--------------------------------------------------------------------------------*/

PGM *IniciaPGM_Saida(PGM *img);

/*--------------------------------------------------------------------------------
Protótipo: PGM *IniciaPGM_Saida(PGM *img)
Função: Gera a partir da imagem de entrada uma imagem auxiliar no processamento da convolução
Entrada: Imagem igual a imagem lida
Saida: Imagem auxiliar para o processo de convolução
--------------------------------------------------------------------------------*/

#endif // PGM_INCLUDED
