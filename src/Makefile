# Nome do executável
TARGET = ted

# Nome do aluno
ALUNO = renanjusan

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb

# Diretório de código-fonte
SRC_DIR = .

# Diretório de cabeçalhos
INC_DIR = .

# Diretório de bibliotecas
LIB_DIR = ./lib

# Bibliotecas adicionais (use -lm para a biblioteca matemática, por exemplo)
LIBS = -lm

# Lista de arquivos de origem
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Lista de arquivos de objeto
OBJETOS = $(SRCS:.c=.o)

# Incluir diretórios
INC_FLAGS = -I$(INC_DIR)

# Diretórios de bibliotecas
LIB_FLAGS = -L$(LIB_DIR)

# Regra de compilação dos arquivos de objeto
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Regra de compilação do executável
$(TARGET): $(OBJETOS)
	$(CC) $(CFLAGS) $(OBJETOS) $(LIB_FLAGS) $(LIBS) -o $(TARGET)

# Limpar arquivos intermediários e o executável
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# Falso alvo para evitar conflitos com arquivos chamados "clean"
.PHONY: clean

pack: $(PROJ_NAME)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/*.c src/*.h src/Makefile LEIA-ME.txt .entrega	