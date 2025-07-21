#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enderecos.h"

typedef struct stRua {
    char *nome;
    char *lesq;
    char *ldir;
    double velocidade;
    double comprimento;
} stRua;

typedef struct stQuadra {
    char *nome;
    char *corb, *corp;
    char *sw;
    double ancx, ancy;
    double w, h;
} stQuadra;


typedef struct stEsquina {
    char *nome;
    double x, y;
} stEsquina;


Quadra createQuadra(char *nome, double ancx, double ancy, double w, double h, char *corb, char *corp, char *sw) {
    stQuadra *q = malloc(sizeof(stQuadra));

    q->ancx = ancx;
    q->ancy = ancy;
    q->w = w;
    q->h = h;

    q->nome = (char*)malloc(strlen(nome)+1);
    if(q->nome == NULL) {
        printf("Erro na alocação de memória do nome da quadra.");
        exit(1);
    }
    strcpy(q->nome, nome);

    q->corb = (char*)malloc(strlen(corb)+1);
    if(q->corb == NULL) {
        printf("Erro na alocação de memória da cor da borda da quadra.");
        exit(1);
    }
    strcpy(q->corb, corb);

    q->corp = (char*)malloc(strlen(corp)+1);
    if(q->corp == NULL) {
        printf("Erro na alocação de memória da cor de preenchimento da quadra.");
        exit(1);
    }
    strcpy(q->corp, corp);

    q->sw = (char*)malloc(strlen(sw)+1);
    if(q->sw == NULL) {
        printf("Erro na alocação de memória da largura da borda da quadra.");
        exit(1);
    }
    strcpy(q->sw, sw);

    return ((stQuadra*)q);
}

char* getNomeQuadra(Quadra q) {
    return ((stQuadra*)q)->nome;
}

double getXQuadra(Quadra q) {
    return ((stQuadra*)q)->ancx;
}

double getYQuadra(Quadra q) {
    return ((stQuadra*)q)->ancy;
}

double getWQuadra(Quadra q) {
    return ((stQuadra*)q)->w;
}

double getHQuadra(Quadra q) {
    return ((stQuadra*)q)->h;
}

char* getCorbQuadra(Quadra q) {
    return ((stQuadra*)q)->corb;  
}

char* getCorpQuadra(Quadra q) {
    return ((stQuadra*)q)->corp;  
}

char* getSWQuadra(Quadra q) {
    return ((stQuadra*)q)->sw;  
}

void setNomeQuadra(Quadra q, char *nome) {
    strcpy(((stQuadra*)q)->nome, nome);
}

void setXQuadra(Quadra q, double x) {
    ((stQuadra*)q)->ancx = x;
}

void setYQuadra(Quadra q, double y) {
    ((stQuadra*)q)->ancy = y;
}

void setWQuadra(Quadra q, double w) {
    ((stQuadra*)q)->w = w;
}

void setHQuadra(Quadra q, double h) {
    ((stQuadra*)q)->h = h;
}

void setCorbQuadra(Quadra q, char *corb) {
    strcpy(((stQuadra*)q)->corb, corb);
}

void setCorpQuadra(Quadra q, char *corp) {
    strcpy(((stQuadra*)q)->corp, corp);
}

void setSWQuadra(Quadra q, char *sw) {
    strcpy(((stQuadra*)q)->sw, sw);
}


Rua createRua(char *nome, char *lesq, char *ldir, double comprimento, double velocidade) {
    stRua *r = malloc(sizeof(stRua));

    r->nome = (char*)malloc(strlen(nome)+1);
    if(r->nome == NULL) {
        printf("Erro na alocacao do nome da Rua.\n");
        exit(1);
    }
    strcpy(r->nome, nome);

    r->ldir = (char*)malloc(strlen(ldir)+1);
    if(r->ldir == NULL) {
        printf("Erro na alocacao do ldir da Rua.\n");
        exit(1);
    }
    strcpy(r->ldir, ldir);

    r->lesq = (char*)malloc(strlen(lesq)+1);
    if(r->lesq == NULL) {
        printf("Erro na alocacao do lesq da Rua.\n");
        exit(1);
    }
    strcpy(r->lesq, lesq);

    r->comprimento = comprimento;
    r->velocidade = velocidade;

    return ((stRua*)r);
}

char* getNomeRUa(Rua r) {
    return ((stRua*)r)->nome;
}

char* getLDIRRua(Rua r) {
    return ((stRua*)r)->ldir;
}

char* getLESQRua(Rua r) {
    return ((stRua*)r)->lesq;
}

double getComprimentoRua(Rua r) {
    return ((stRua*)r)->comprimento;
}

double getVelocidadeRua(Rua r) {
    return ((stRua*)r)->velocidade;
}

void setNomeRUa(Rua r, char *nome) {
    strcpy(((stRua*)r)->nome, nome);
}

void setLDIRRua(Rua r, char *ldir) {
    strcpy(((stRua*)r)->ldir, ldir);
}

void setLESQRua(Rua r, char *lesq) {
    strcpy(((stRua*)r)->lesq, lesq);
}

void setCompRua(Rua r, double comp) {
    ((stRua*)r)->comprimento = comp;
}

void setVelocidadeRua(Rua r, double veloc) {
    ((stRua*)r)->velocidade = veloc;
}




Esquina createEsquina(char *nome, double x, double y) {
    stEsquina *e = malloc(sizeof(stEsquina));

    e->x = x;
    e->y = y;

    e->nome = (char*)malloc(strlen(nome)+1);
    if(e->nome == NULL) {
        printf("Erro na alocacao do nome da Esquina.\n");
        exit(1);
    }
    strcpy(e->nome, nome);

    return ((stEsquina*)e);
}

char* getNomeEsquina(Esquina eq) {
    return ((stEsquina*)eq)->nome;
}

double getXEsquina(Esquina eq) {
    return ((stEsquina*)eq)->x;
}

double getYEsquina(Esquina eq) {
    return ((stEsquina*)eq)->y;
}


void setNomeEsquina(Esquina eq, char *nome) {
    strcpy(((stEsquina*)eq)->nome, nome);
}

void setXEsquina(Esquina eq, double x) {
    ((stEsquina*)eq)->x = x;
}

void setYEsquina(Esquina eq, double y) {
    ((stEsquina*)eq)->y = y;
}

void calculaBoundingBoxEsquina(Esquina eq, double *x, double *y, double *w, double *h) {
    *x = getXEsquina(eq);
    *y = getYEsquina(eq);
    *w = 0;
    *h = 0;
}
