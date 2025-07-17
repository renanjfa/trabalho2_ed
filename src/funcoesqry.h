#ifndef FUNCOESQRY_H
#define FUNCOESQRY_H

#include "graph.h"
#include "smutreap.h"
#include "lista.h"
#include "hash_table.h"

void registrarEndereco(FILE* svg, FILE* txt, HashTable enderecos, HashTable quadras, char *nomereg, char *cep, char face, int num);

// rpeortar svg e txt
void alag(FILE* svg, FILE* txt, Graph g, SmuTreap t, int n, double x, double y, double w, double h, Lista *arestasN);

// reportar txt
void dren(FILE* txt, Graph g, int n, Lista *arestasN);

void sg(char *nome, double x, double y, double w, double h);

void registrarPercurso(char *np, char *nome, char *reg1, char *reg2);

void join(char *np, char *np1, char *np2);

void shw(FILE* svg, char *np, char *cmc, char *cmr, HashTable percursos);


#endif