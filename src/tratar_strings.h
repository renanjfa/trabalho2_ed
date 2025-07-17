#ifndef TRATAR_STRINGS_H
#define TRATAR_STRINGS_H

#include <stdbool.h>

char* trataDirEntrada(const char *str);

char* getNomeGeo(const char *arqgeo);

char* getNomeQry(const char *arqry);

char* concatenaNomeQry(const char* nomegeo, const char* nomeqry);

char* getNomeVia(const char *arqvia);

bool leituraLinha(FILE* arq, char *linha, int max_size);

#endif