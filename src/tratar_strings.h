#ifndef TRATAR_STRINGS_H
#define TRATAR_STRINGS_H

#include <stdbool.h>

/*
    TRATAR_STRINGS.H:
    Modulo responsável por fazer o tratamento de strings e arquivos ao longo do projeto.
*/

char* trataDirEntrada(const char *str);

char* getNomeGeo(const char *arqgeo);

char* getNomeQry(const char *arqry);

char* concatenaNomeQry(const char* nomegeo, const char* nomeqry);

char* getNomeVia(const char *arqvia);

bool leituraLinha(FILE* arq, char *linha, int max_size);

#endif