#include "image.h"

IMAGEM LerImagem(IMAGEM *img, char *imgName, char *imgFormat){
	int tamanhoImagem;
	FILE *fonte;
	
	if((fonte = fopen(imgName, "rb"))==NULL){
		printf("ERRO: %s - Arquivo ou diretório não encontrado.\n", imgName);
	}else{
		if(strcmp(imgFormat, "ppm") == 0){
			LerCabPPM(img, fonte);
		}else if(strcmp(imgFormat, "bmp") == 0){
			LerCabBMP(img, fonte);
		}
		
		tamanhoImagem = Get_TamanhoImagem(img, imgFormat);
	
		img->dados = LerDados(img, fonte, tamanhoImagem);
	}
	
	return *img;
}


/*Função que lê o cabecalho de imagens do tipo ppm*/
void LerCabPPM(IMAGEM *img, FILE *fonte){
	fscanf(fonte, "%s", img->cabPPM.tipo);
	fscanf(fonte, "%d%d", &img->cabPPM.largura, &img->cabPPM.altura);
	fscanf(fonte, "%d", &img->cabPPM.maximo);
}


/*Função que lê o cabecalho de imagens do tipo bmp*/
void LerCabBMP(IMAGEM *img, FILE *fonte){
	fread(img->cabecalho.identificador, sizeof(img->cabecalho.identificador), 1, fonte);
	fread(&img->cabecalho.tamanho, sizeof(img->cabecalho.tamanho), 1, fonte);
	fread(&img->cabecalho.areaReservada1, sizeof(img->cabecalho.areaReservada1), 1, fonte);
	fread(&img->cabecalho.areaReservada2, sizeof(img->cabecalho.areaReservada2), 1, fonte);
	fread(&img->cabecalho.enderecoInicial, sizeof(img->cabecalho.enderecoInicial), 1, fonte);
	
	fread(&img->mapaBits.tamanho, sizeof(img->mapaBits.tamanho), 1, fonte);
	fread(&img->mapaBits.largura, sizeof(img->mapaBits.largura), 1, fonte);
	fread(&img->mapaBits.altura, sizeof(img->mapaBits.altura), 1, fonte);
	fread(&img->mapaBits.planosCor, sizeof(img->mapaBits.planosCor), 1, fonte);
	fread(&img->mapaBits.bpp, sizeof(img->mapaBits.bpp), 1, fonte);
	fread(&img->mapaBits.metodoCompressao, sizeof(img->mapaBits.metodoCompressao), 1, fonte);
	fread(&img->mapaBits.tamanhoImagem, sizeof(img->mapaBits.tamanhoImagem), 1, fonte);
	fread(&img->mapaBits.resolucaoHorizontal, sizeof(img->mapaBits.resolucaoHorizontal), 1, fonte);
	fread(&img->mapaBits.resolucaoVertical, sizeof(img->mapaBits.resolucaoVertical), 1, fonte);
	fread(&img->mapaBits.coresPaleta, sizeof(img->mapaBits.coresPaleta), 1, fonte);
	fread(&img->mapaBits.coresImportantes, sizeof(img->mapaBits.coresImportantes), 1, fonte);
}

int Get_TamanhoImagem(IMAGEM *img, char *imgFormat){
	int tamanhoImagem;
	
	if(strcmp(imgFormat, "ppm") == 0){
		tamanhoImagem = img->cabPPM.largura * img->cabPPM.altura;
	}else if(strcmp(imgFormat, "bmp") == 0){
		tamanhoImagem = img->mapaBits.largura * img->mapaBits.altura;
	}
	
	return tamanhoImagem;
}


/*Função que lê os pixels da imagem*/
PIXEL *LerDados(IMAGEM *img, FILE *fonte, int tamanhoImagem){
	int i;
	
	img->dados = (PIXEL *)malloc((tamanhoImagem/4)*sizeof(PIXEL));
		for(i = 0; i < (tamanhoImagem/4); i++){
			fread(&img->dados[i], sizeof(PIXEL), 1, fonte);
		}
		
	return img->dados;
}

void EscreverImagem(IMAGEM *img, int tamanhoImagem, char *imgFormat){
	FILE *destino;
	int i;
	if(strcmp(imgFormat, "ppm") == 0){
		if((destino = fopen("codificada.ppm", "wb")) != NULL){
			fprintf(destino, "%s\n", img->cabPPM.tipo);
			fprintf(destino, "%d %d\n", img->cabPPM.largura, img->cabPPM.altura);
			fprintf(destino, "%d", img->cabPPM.maximo);
		}
	}else if(strcmp(imgFormat, "bmp") == 0){
		if((destino = fopen("codificada.bmp", "wb")) != NULL){
			fwrite(img->cabecalho.identificador, sizeof(img->cabecalho.identificador), 1, destino);
			fwrite(&img->cabecalho.tamanho, sizeof(img->cabecalho.tamanho), 1, destino);
			fwrite(&img->cabecalho.areaReservada1, sizeof(img->cabecalho.areaReservada1), 1, destino);
			fwrite(&img->cabecalho.areaReservada2, sizeof(img->cabecalho.areaReservada2), 1, destino);
			fwrite(&img->cabecalho.enderecoInicial, sizeof(img->cabecalho.enderecoInicial), 1, destino);
		
			fwrite(&img->mapaBits.tamanho, sizeof(img->mapaBits.tamanho), 1, destino);
			fwrite(&img->mapaBits.largura, sizeof(img->mapaBits.largura), 1, destino);
			fwrite(&img->mapaBits.altura, sizeof(img->mapaBits.altura), 1, destino);
			fwrite(&img->mapaBits.planosCor, sizeof(img->mapaBits.planosCor), 1, destino);
			fwrite(&img->mapaBits.bpp, sizeof(img->mapaBits.bpp), 1, destino);
			fwrite(&img->mapaBits.metodoCompressao, sizeof(img->mapaBits.metodoCompressao), 1, destino);
			fwrite(&img->mapaBits.tamanhoImagem, sizeof(img->mapaBits.tamanhoImagem), 1, destino);
			fwrite(&img->mapaBits.resolucaoHorizontal, sizeof(img->mapaBits.resolucaoHorizontal), 1, destino);
			fwrite(&img->mapaBits.resolucaoVertical, sizeof(img->mapaBits.resolucaoVertical), 1, destino);
			fwrite(&img->mapaBits.coresPaleta, sizeof(img->mapaBits.coresPaleta), 1, destino);
			fwrite(&img->mapaBits.coresImportantes, sizeof(img->mapaBits.coresImportantes), 1, destino);
		}
	}
	
		for(i = 0; i < (tamanhoImagem/4); i++){
			fwrite(&img->dados[i], sizeof(PIXEL), 1, destino);
		}
}
