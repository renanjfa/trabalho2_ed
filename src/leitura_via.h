#ifndef LEITURA_VIA_H
#define LEITURA_VIA_H

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "smutreap.h"

Graph LeituraCompletaVia(FILE *arqvia, SmuTreap t);

Graph ProcessaVia(const char *pathvia, SmuTreap t);


#endif