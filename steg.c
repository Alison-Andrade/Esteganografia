#include "steg.h"

void Encoder(IMAGEM *img, char *inputFile, char *imgFormat, char *imgName){
	
	int tamanhoImagem, tamanhoMensagem;
	char *mensagem;
	char saida[15] = "codificada.";
	strcat(saida, imgFormat);
	
	printf("Lendo imagem...\n\n");
	LerImagem(img, imgName, imgFormat);
	
	tamanhoImagem = Get_TamanhoImagem(img, imgFormat);
	
	printf("Lendo mensagem...\n\n");
	mensagem = LerMensagem(inputFile, tamanhoImagem);
	
	tamanhoMensagem = strlen(mensagem);
	
	
/*	Verificaçao do tamanho da imagem e da mensagem para saber se a imagem comporta a mensagem	*/
	if(tamanhoImagem < tamanhoMensagem){
		printf("ERRO: Mensagem muito longa para imagem.\n");
	}else{
		printf("MENSAGEM A SER INSERIDA: \"%s\"\n", mensagem);
		
		printf("Inserindo mensagem...\n");
		img->dados = InserirMensagem(img, mensagem);
		
		EscreverImagem(img, tamanhoImagem, imgFormat);
		printf("Um arquivo \"%s\" foi criado em seu diretório atual.\n", saida);
	}
	
}

char *LerMensagem(char *inputFile, int tamanhoImagem){
	char *texto;
	
	FILE *mensagem;
	
	if((mensagem = fopen(inputFile, "r")) == NULL){
		printf("ERRO: %s - Arquivo ou diretório não encontrado.\n", inputFile);
	}else{
		texto = (char *)malloc(tamanhoImagem*sizeof(char));
	
		fscanf(mensagem, "%[^\n]s", texto);
	}
	
	fclose(mensagem);
	
	return texto;
	
	free(mensagem);
}

PIXEL *InserirMensagem(IMAGEM *img, char *mensagem){
	int i, numCaractere;
	int tamanhoMensagem = strlen(mensagem);
	
	printf("Tamanho da mensagem a ser inserida: %d bytes\n", tamanhoMensagem);
	
/*		Serão pegos 3 pixels da imagem por vez, assim teremos um total de 9 bits,
		será feita então a substituição do bit menos significativo de 8 deles por bits da mensagem.	*/
	
	for(numCaractere = 0, i = 1; numCaractere <= tamanhoMensagem; numCaractere++){
		
		img->dados[i].red &= 254;
        img->dados[i].green &= 254;
        img->dados[i].blue &= 254;
        
        img->dados[i].red ^= (mensagem[numCaractere] & 1 ? 1 : 0);
        img->dados[i].green ^= (mensagem[numCaractere] & 2 ? 1 : 0);
        img->dados[i].blue ^= (mensagem[numCaractere] & 4 ? 1 : 0);
        i++;
        
        img->dados[i].red &= 254;
        img->dados[i].green &= 254;
        img->dados[i].blue &= 254;
        
        img->dados[i].red ^= (mensagem[numCaractere] & 8 ? 1 : 0);
        img->dados[i].green ^= (mensagem[numCaractere] & 16 ? 1 : 0);
        img->dados[i].blue ^= (mensagem[numCaractere] & 32 ? 1 : 0);
        i++;
        
        img->dados[i].red &= 254;
        img->dados[i].green &= 254;
        
        img->dados[i].red ^= (mensagem[numCaractere] & 64 ? 1 : 0);
        img->dados[i].green ^= (mensagem[numCaractere] & 128 ? 1 : 0);
        i++;
	}
	
	return img->dados;
}

void Decoder(IMAGEM *img, char *outputFile, char *imgFormat, char *imgName){
	
	int tamanhoImagem;
	
	printf("Lendo imagem...\n\n");
	LerImagem(img, imgName, imgFormat);
	
	tamanhoImagem = Get_TamanhoImagem(img, imgFormat);
	printf("Extraindo mensagem...\n\n");
	ExtrairMensagem(img, outputFile, tamanhoImagem);
	printf("Um arquivo \"%s\" foi criado em seu diretório atual.\n", outputFile);
	
}

void ExtrairMensagem(IMAGEM *img, char *outputFile, int tamanhoImagem){
	int i = 1, j = 0;
	char caractere;
	char *mensagem;
	
	FILE *out;
	
	mensagem = (char *)malloc(tamanhoImagem*sizeof(char));
	
	do{
		caractere = ((img->dados[i].red)&1)+
					((img->dados[i].green & 1) * 2)+
					((img->dados[i].blue&1) * 4)+
					((img->dados[i+1].red & 1) * 8)+
					((img->dados[i+1].green & 1) * 16)+
					((img->dados[i+1].blue & 1) * 32)+
					((img->dados[i+2].red & 1) * 64)+
					((img->dados[i+2].green & 1) * 128);
		i+=3;			
					
		mensagem[j] = caractere;
		j++;
	}while((caractere != '\0'));
	
	out = fopen(outputFile, "w");
	
	fprintf(out, "%s", mensagem);
	
	free(mensagem);
}


