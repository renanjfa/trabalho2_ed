#ifndef REGISTRADORES_H
#define REGISTRADORES_H

typedef void *Endereco;
typedef void *Percurso;
typedef void *Coordenadas;

#include "lista.h"
#include "hash_table.h"

/* ----- CONSTRUTOR ENDERECO ----- */

Endereco createEndereco(char *nomeQuadra, char setor, int numero, HashTable quadras);

/* ----- METODOS GET ENDERECO ----- */

char* getNomeQuadraEndereco(Endereco e);

char getSetorEndereco(Endereco e);

int getNumeroEndereco(Endereco e);

double getXEndereco(Endereco e);

double getYEndereco(Endereco e);

/* ----- METODOS SET ENDERECO ----- */

void setNomeQuadraEndereco(Endereco e, char *nome);

void setSetorEndereco(Endereco e, char setor);

void setNumeroEndereco(Endereco e, int num);

void setXEndereco(Endereco e, double x);

void setYEndereco(Endereco e, double y);




/* ----- CONSTRUTOR PERCURSO ----- */

Percurso createPercurso(char *nome, char *origem, char *destino);

/* ----- METODOS GET PERCURSO ----- */

char* getNomePercurso(Percurso p);

char* getOrigemPercurso(Percurso p);

char* getDestinoPercurso(Percurso p);

Lista getPathCMRPercurso(Percurso p);

Lista getPathCMCPercurso(Percurso p);

/* ----- METODOS SET PERCURSO ----- */

void setNomePercurso(Percurso p, char *nome);

void setOrigemPercurso(Percurso p, char *origem);

void setDestinoPercurso(Percurso p, char *destino);

/* ----- METODOS EXTRAS AUXILIARES PERCURSO ----- */

void insertPathCMRPercurso(Percurso p, Coordenadas c);
    
void insertPathCMCPercurso(Percurso p, Coordenadas c);




/* ----- CONSTRUTOR COORDENADAS ----- */

Coordenadas createCoordenadas(double x, double y);

/* ----- METODOS GET COORDENADAS ----- */

double getXCoord(Coordenadas c);

double getYCoord(Coordenadas c);

/* ----- METODOS SET COORDENADAS ----- */

void setXCoord(Coordenadas c, double x);

void setYCoord(Coordenadas c, double y);

#endif