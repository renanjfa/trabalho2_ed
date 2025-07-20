#ifndef LEITURA_CIDADE_H
#define LEITURA_CIDADE_H

#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

HashTable LeituraCompletaCidade(FILE **svg1, FILE *arqcidade, HashTable ht);

HashTable ProcessaCidade(const char *pathcidade, const char *dirsaida, const char *nomecidade);


#endif
