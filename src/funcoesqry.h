#ifndef FUNCOESQRY_H
#define FUNCOESQRY_H

#include "graph.h"
#include "smutreap.h"
#include "lista.h"
#include "hash_table.h"

/*
    FUNCOESQRY.H
    Módulo responsável pelas funções componentes do arquivo .qry de consulta.
*/

void registrarEndereco(FILE* svg, FILE* txt, HashTable enderecos, HashTable quadras, char *nomereg, char *cep, char face, int num);

void alag(FILE* svg, FILE* txt, Graph g, SmuTreap t, int n, double x, double y, double w, double h, Lista *arestasN);

void dren(FILE* txt, Graph g, int n, Lista *arestasN);

void sg(FILE* svg, Graph g, SmuTreap t, char *nome, double x, double y, double w, double h);

void registrarPercurso(FILE* txt, Graph g, SmuTreap t, HashTable enderecos, HashTable percursos, char *np, char *nome, char *reg1, char *reg2);

void join(FILE* txt, Graph g, SmuTreap t, HashTable percursos, char *np, char *np1, char *np2);

void shw(FILE* svg, char *np, char *cmc, char *cmr, HashTable percursos);


#endif