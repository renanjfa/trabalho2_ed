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

Graph LeituraCompletaVia(FILE *arqvia, SmuTreap t);

Graph ProcessaVia(const char *pathvia, SmuTreap t);


#endif