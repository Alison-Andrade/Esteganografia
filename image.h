#ifndef IMAGE_H
#define IMAGE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int red;
	int green;
	int blue;
}PIXEL;

typedef struct{
	char identificador[2];
	int tamanho;
	short int areaReservada1;
	short int areaReservada2;
	int enderecoInicial;
}CABECALHOBITMAP;

typedef struct{
	int tamanho;
	int largura;
	int altura;
	short int planosCor;
	short int bpp;
	int metodoCompressao;
	int tamanhoImagem;
	int resolucaoHorizontal;
	int resolucaoVertical;
	int coresPaleta;
	int coresImportantes;
}CABECALHOMAPABITS;

typedef struct{
	char tipo[2];
	int largura;
	int altura;
	int maximo;
}CABECALHOPPM;

typedef struct{
	CABECALHOBITMAP cabecalho;
	CABECALHOMAPABITS mapaBits;
	CABECALHOPPM cabPPM;
	PIXEL *dados;
}IMAGEM;
/*--------------------------------------------------------------------*/
/*-------------Funções para leitura e escrita da imagem---------------*/
/*--------------------------------------------------------------------*/

IMAGEM LerImagem(IMAGEM *img, char *imgName, char *imgFormat);

void LerCabPPM(IMAGEM *img, FILE *fonte);

void LerCabBMP(IMAGEM *img, FILE *fonte);

int Get_TamanhoImagem(IMAGEM *img, char *imgFormat);//Retorna o espaço total que pode ser utilizado para gardar a mensagem.

PIXEL *LerDados(IMAGEM *img, FILE *fonte, int tamanhoImagem);

void EscreverImagem(IMAGEM *img, int tamanhoImagem, char *imgFormat);

#endif /* IMAGE_H */


