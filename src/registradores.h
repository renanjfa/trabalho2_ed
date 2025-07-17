#ifndef REGISTRADORES_H
#define REGISTRADORES_H

typedef void *Endereco;
typedef void *Percurso;


/* ----- CONSTRUTOR ENDERECO ----- */

Endereco createEndereco(char *nomeQuadra, char setor, int numero);

/* ----- METODOS GET ENDERECO ----- */

char* getNomeQuadraEndereco(Endereco e);

char getSetorEndereco(Endereco e);

int getNumeroEndereco(Endereco e);

/* ----- METODOS SET ENDERECO ----- */

void setNomeQuadraEndereco(Endereco e, char *nome);

void setSetorEndereco(Endereco e, char setor);

void setNumeroEndereco(Endereco e, int num);




/* ----- CONSTRUTOR PERCURSO ----- */

Percurso createPercurso(char *nome, char *origem, char *destino);

/* ----- METODOS GET PERCURSO ----- */

char* getNomePercurso(Percurso p);

char* getOrigemPercurso(Percurso p);

char* getDestinoPercurso(Percurso p);

/* ----- METODOS SET PERCURSO ----- */

void setNomePercurso(Percurso p, char *nome);

void setOrigemPercurso(Percurso p, char *origem);

void setDestinoPercurso(Percurso p, char *destino);



#endif