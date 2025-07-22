#ifndef LEITURA_VIA_H
#define LEITURA_VIA_H

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "smutreap.h"

/*
    LEITURA_VIA.H
    Módulo responsável pela leitura de um arquivo .via que descreve o comportamento de um grafo direcionado.
*/

/*
    Realiza a leitura completa do arquivo .via responsável por descrever as características do sistema viário de uma cidade.
    Retorna um grafo que simula o sistema viário da cidade.
*/
Graph LeituraCompletaVia(FILE *arqvia, SmuTreap t);


/*
    Processa o arquivo .via usando seu path, preparando-o para sua leitura.
    Retorna um grafo que simula o sistema viário da cidade.
*/
Graph ProcessaVia(const char *pathvia, SmuTreap t);


#endif