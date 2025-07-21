#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registradores.h"
#include "lista.h"
#include "hash_table.h"
#include "enderecos.h"

typedef struct stCoord {
    double x, y;
} stCoord;

typedef struct stEndereco {
    double x, y;
    char *nomeQuadra;
    char setor;
    int numero; // distancia da projecao da ancora
} stEndereco;

typedef struct stPercurso {
    char *nome;
    Endereco origem;
    Endereco destino;
    Lista path_cmc;
    Lista path_cmr;
} stPercurso;


void calcularCoordenadaEndereco(Endereco e, HashTable quadras, double *x, double *y) {
    Quadra q = buscaHashTable(quadras, getNomeQuadraEndereco(e));
    if(!q) {
        printf("Quadra nao encontrada em quadras\n");
        return;
    }

    double ancx = getXQuadra(q);
    double ancy = getYQuadra(q);
    double w = getWQuadra(q);
    double h = getHQuadra(q);

    int num = getNumeroEndereco(e);

    switch(getSetorEndereco(e)) {
        case 'S':
            *x = ancx + num;
            *y = ancy;
            break;
        case 'L':
            *x = ancx;
            *y = ancy + num;
            break;
        case 'N':
            *x = ancx + num;
            *y = ancy + h;
            break;
        case 'O':
            *x = ancx + w;
            *y = ancy + num;
            break;
        default:
            return;
    }
}

Endereco createEndereco(char *nomeQuadra, char setor, int numero, HashTable quadras) {
    stEndereco *e = malloc(sizeof(stEndereco));

    e->nomeQuadra = (char*)malloc(strlen(nomeQuadra)+1);
    if(e->nomeQuadra == NULL) {
        printf("Erro na alocacao do nomeQuadra do Endereco.\n");
        exit(1);
    }
    strcpy(e->nomeQuadra, nomeQuadra);

    e->setor = setor;

    e->numero = numero;

    double x, y;
    calcularCoordenadaEndereco(e, quadras, &x, &y);

    e->x = x;
    e->y = y;

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

double getXEndereco(Endereco e) {
    return ((stEndereco*)e)->x;
}

double getYEndereco(Endereco e) {
    return ((stEndereco*)e)->y;
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

void setXEndereco(Endereco e, double x) {
    ((stEndereco*)e)->x = x;
}

void setYEndereco(Endereco e, double y) {
    ((stEndereco*)e)->y = y;
}


Percurso createPercurso(char *nome, Endereco origem, Endereco destino) {
    stPercurso *p = malloc(sizeof(stPercurso));

    p->nome = (char*)malloc(strlen(nome)+1);
    if(p->nome == NULL) {
        printf("Erro na alocacao do nome percurso.\n");
        exit(1);
    }
    strcpy(p->nome, nome);

    p->origem = origem;
    p->destino = destino;

    p->path_cmc = criaLista();
    p->path_cmr = criaLista();

    return ((stPercurso*)p);
}


char* getNomePercurso(Percurso p) {
    return ((stPercurso*)p)->nome;
}


Endereco getOrigemPercurso(Percurso p) {
    return ((stPercurso*)p)->origem;
}

Endereco getDestinoPercurso(Percurso p) {
    return ((stPercurso*)p)->destino;
}


void setNomePercurso(Percurso p, char *nome) {
    strcpy(((stPercurso*)p)->nome, nome);
}


void insertPathCMRPercurso(Percurso p, Coordenadas c) {
    insereLista(((stPercurso*)p)->path_cmr, c);
}

void insertPathCMCPercurso(Percurso p, Coordenadas c) {
    insereLista(((stPercurso*)p)->path_cmc, c);
}

Lista getPathCMRPercurso(Percurso p) {
    return ((stPercurso*)p)->path_cmr;
}

Lista getPathCMCPercurso(Percurso p) {
    return ((stPercurso*)p)->path_cmc;
}


Coordenadas createCoordenadas(double x, double y) {
    stCoord *c = malloc(sizeof(stCoord));

    c->x = x;
    c->y = y;

    return ((stCoord*)c);
}

double getXCoord(Coordenadas c) {
    return ((stCoord*)c)->x;
}

double getYCoord(Coordenadas c) {
    return ((stCoord*)c)->y;
}

void setXCoord(Coordenadas c, double x) {
    ((stCoord*)c)->x = x;
}

void setYCoord(Coordenadas c, double y) {
    ((stCoord*)c)->y = y;
}