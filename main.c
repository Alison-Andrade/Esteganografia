#include <stdio.h>
#include <unistd.h>
#include "steg.h"


/*----------------------------------------------------------------------------------------------------*/
/*-------------------------------Função para impressão de Instruções----------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
void ShowHelp(){
	
	printf("Não foram passados parametros suficientes.\n");
	printf("Exemplos:\n");
	printf("CODIFICAR:\n	./steg -e -i \"arquivo da mensagem\" -f \"extenção da imagem\" \"nome da imagem\"\n");
	printf("DECODIFICAR:\n	./steg -d -o \"arquivo da mensagem\" -f \"extenção da imagem\" \"nome da imagem\"\n");
	
}

int main (int argc, char *argv[]){
	
	int opt;
	int eFlag = 0, dFlag = 0;
	char *inputFile = NULL, *outputFile = NULL, *imgFormat = NULL, *imgName = NULL;
	IMAGEM img;
	
/*----------------------------------------------------------------------------------------------------*/
/*----------------------------Função getopt para passagem de parametros-------------------------------*/
/*----------------------------------------------------------------------------------------------------*/
	while((opt = getopt(argc, argv, "edi:o:f:")) > 0){
		switch(opt){
			case 'e':
				eFlag = 1;
				break;
			case 'd':
				dFlag = 1;
				break;
			case 'i':
				inputFile = optarg;
				break;
			case 'o':
				outputFile = optarg;
				break;
			case 'f':
				imgFormat = optarg;
				break;
		}
	}
	
		if((argv[optind] != NULL)) imgName = argv[optind];/*----------------------------------------------------------------------------------------------------*/
	
	if(eFlag == 1 && inputFile != NULL && imgFormat != NULL && imgName != NULL){
		Encoder(&img, inputFile, imgFormat, imgName);
	}else if(dFlag == 1 && outputFile != NULL && imgFormat != NULL && imgName != NULL){
		Decoder(&img, outputFile, imgFormat, imgName);
	}else{
		ShowHelp();
	}
	
	return 0;
}

