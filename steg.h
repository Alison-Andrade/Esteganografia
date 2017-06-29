#ifndef STEG_H
#define  STEG_H

#include "image.h"


void Encoder(IMAGEM *img, char *inputFile, char *imgFormat, char *imgName);

char *LerMensagem(char *inputFile, int tamanhoImagem);

PIXEL *InserirMensagem(IMAGEM *img, char *mensagem);

/*------------------------------------------------------------------*/

void Decoder(IMAGEM *img, char *outputFile, char *imgFormat, char *imgName);

void ExtrairMensagem(IMAGEM *img, char *outputFile, int tamanhoImagem);

#endif /*  STEG_H */

