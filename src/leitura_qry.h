#ifndef LEITURA_QRY_H
#define LEITURA_QRY_H

#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "hash_table.h"
#include "graph.h"
#include "smutreap.h"

/*
    LEITURA_QRY.H
    Módulo responsável pela leitura de um arquivo .qry de consulta.
*/

/*
    Realiza a leitura do arquivo de consulta .qry fornecido, realizando as funções e comandos de consulta especificados no arquivo.
*/
void LeituraCompletaQry(FILE* arqQry, FILE **txt, FILE **svgs2, Graph g, SmuTreap smuVertices, HashTable quadras, HashTable enderecos, HashTable percursos, Lista *arestasN);


/*
    Processa o arquivo .qry fornecido por seu path, preparando-o para sua leitura.
*/
void ProcessaQry(const char *pathqry, const char *dirSaida, const char *nomearqsaida, const char *nomeqry, Graph g, SmuTreap smuVertices, HashTable quadras, HashTable enderecos, HashTable percursos, Lista *arestasN);


#endif