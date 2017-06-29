Projeto de conclusão das disciplinas de Introdução as Técnicas de Programação e Praticas de Técnicas de Programação.

------------------------------------------------Esteganografia----------------------------------------------

	-Foram implementadas as funcionalidades de codificação e decodificação de mensagens em imagens nos formatos PPM e BMP, também.

	-COMPILAÇÃO

	Acompanha o código fonte um arquivo Makefile.
	Para compilação com o Makefile, basta digitar o comando "make" no terminal, será criado um executável com nome "steg" em seu diretório.
	Para compilação sem MAkefile, digite "gcc -W -Wall -pedantic main.c image.c steg.c -o nome_do_programa".
	
	-EXECUÇÃO
	
		Codificar:
			./steg -e -i "arquivo de texto" -f "formato (ppm ou pmp)" "imagem"
			
			-e: indica que o programa executará em modo codificador;
			-i: recebe como parâmetro o arquivo de texto que contem sua mensagem;
			-f: formato da imagem que receberá a mensagem;
			Por último segue o caminho da imagem que hospedará a mensagem.
			
		Decodificar:
			./steg -d -o "arquivo de texto" -f "formato (ppm ou pmp)" "imagem"
			
			-d: indica que o programa executará em modo decodificador;
			-o: recebe como parâmetro o arquivo de texto onde será salva sua mensagem;
			-f: formato da imagem que contem a mensagem;
			Por último segue o caminho da imagem que contem a mensagem.
			
			
Autores:
	
	Alison Sidnei Ferreira de Andrade
	Marllon Felipe da Silva Lima
