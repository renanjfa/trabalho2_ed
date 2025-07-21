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


EXEC_TESTS = ./ted
DIRBASE  = /mnt/c/COMP_UEL/EDII/Trabalho2/trabalho2_ed
ENTRADA  = $(DIRBASE)/t2/
SAIDA    = $(DIRBASE)/saidas

c1:
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/00-perc-smpl.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/01-joined.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/02-alag-central-perc-smpl.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/03-alag-central-dren-perc-smpl.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/04-alag-esp-perc-smpl.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/05-alag-l-perc-smpl.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/06-perc-estr3.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/07-perc-estr3-showall.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/08-perc-estr3-joinall.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/09-perc-varios-joinall.qry -v c1-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c1.geo -o $(SAIDA) -q c1/10-perc-smpl.qry -v c1-v.via


c2:
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/00-perc-smpl.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/01-joined.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/02-alag-central-perc-smpl.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/03-alag-central-dren-perc-smpl.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/04-alag-esp-perc-smpl.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/05-alag-l-perc-smpl.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/06-perc-estr3.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/07-perc-estr3-showall.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/08-perc-estr3-joinall.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/09-perc-varios-joinall.qry -v c2-v.via
	$(EXEC_TESTS) -e $(ENTRADA) -f c2.geo -o $(SAIDA) -q c2/10-perc-smpl.qry -v c2-v.via

