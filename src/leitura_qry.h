#ifndef LEITURA_QRY_H
#define LEITURA_QRY_H

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "hash_table.h"
#include "graph.h"
#include "smutreap.h"


void LeituraCompletaQry(FILE* arqQry, FILE **txt, FILE **svgs2, Graph g, SmuTreap smuVertices, HashTable quadras, HashTable enderecos, HashTable percursos, Lista *arestasN);

void ProcessaQry(const char *pathqry, const char *dirSaida, const char *nomearqsaida, const char *nomeqry, Graph g, SmuTreap smuVertices, HashTable quadras, HashTable enderecos, HashTable percursos, Lista *arestasN);


#endif