#include <stdio.h>
#include <stdlib.h>

#include "registradores.h"

typedef struct stEndereco {
    char *nomeQuadra;
    char setor;
    int numero; // distancia da projecao da ancora
} stEndereco;

typedef struct stPercurso {
    char *nome;
    char *origem;
    char *destino;
} stPercurso;


Endereco createEndereco(char *nomeQuadra, char setor, int numero) {
    stEndereco *e = malloc(sizeof(stEndereco));

    e->nomeQuadra = (char*)malloc(strlen(nomeQuadra)+1);
    if(e->nomeQuadra == NULL) {
        printf("Erro na alocacao do nomeQuadra do Endereco.\n");
        exit(1);
    }
    strcpy(e->nomeQuadra, nomeQuadra);

    e->setor = setor;

    e->numero = numero;

    return ((stEndereco*)e);
}

char* getNomeQuadraEndereco(Endereco e) {
    return ((stEndereco*)e)->nomeQuadra;
}

char getSetorEndereco(Endereco e) {
    return ((stEndereco*)e)->setor;
}

int getNumeroEndereco(Endereco e) {
    return ((stEndereco*)e)->numero;
}

void setNomeQuadraEndereco(Endereco e, char *nome) {
    strcpy(((stEndereco*)e)->nomeQuadra, nome);
}

void setSetorEndereco(Endereco e, char setor) {
    ((stEndereco*)e)->setor = setor;
}

void setNumeroEndereco(Endereco e, int num) {
    ((stEndereco*)e)->numero = num;
}





Percurso createPercurso(char *nome, char *origem, char *destino) {
    stPercurso *p = malloc(sizeof(stPercurso));

    p->nome = (char*)malloc(strlen(nome)+1);
    if(p->nome == NULL) {
        printf("Erro na alocacao do nome percurso.\n");
        exit(1);
    }
    strcpy(p->nome, nome);

    p->origem = (char*)malloc(strlen(origem)+1);
    if(p->origem == NULL) {
        printf("Erro na alocacao do origem percurso.\n");
        exit(1);
    }
    strcpy(p->origem, origem);

    p->destino = (char*)malloc(strlen(destino)+1);
    if(p->destino == NULL) {
        printf("Erro na alocacao do destino percurso.\n");
        exit(1);
    }
    strcpy(p->destino, destino);

    return ((stPercurso*)p);
}


char* getNomePercurso(Percurso p) {
    return ((stPercurso*)p)->nome;
}

char* getOrigemPercurso(Percurso p) {
    return ((stPercurso*)p)->origem;
}

char* getDestinoPercurso(Percurso p) {
    return ((stPercurso*)p)->destino;
}


void setNomePercurso(Percurso p, char *nome) {
    strcpy(((stPercurso*)p)->nome, nome);
}

void setOrigemPercurso(Percurso p, char *origem) {
    strcpy(((stPercurso*)p)->origem, origem);
}

void setDestinoPercurso(Percurso p, char *destino) {
    strcpy(((stPercurso*)p)->destino, destino);
}