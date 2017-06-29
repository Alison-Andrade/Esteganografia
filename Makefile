CC=gcc
CFLAGS=-W -Wall -pedantic
SRC=main.c steg.c steg.h image.c image.h
OBJ=main.o steg.o image.o

all: steg

steg: $(OBJ)
	@echo Criando arquivo executável: $@
	$(CC) $^ -o $@ -g
%.o: %.c %.h
	@echo Compilando arquivo objeto: $@
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	@echo Limpando arquivos.
	-@rm -f *.o steg *~ codificada.*
	@echo Pronto.
