#ifndef ENDERECOS_H
#define ENDERECOS_H

typedef void *Rua;  
typedef void *Quadra;   
typedef void *Esquina;
/*
    ENDERECOS.H
    Módulo responsável por gerenciar 3 instâncias relacionadas a uma cidade: Rua, Quadra e Esquina.
    Inclui operações básicas para cada instância (Métodos get, set e auxiliares).
*/

/* ----- CONSTRUTOR QUADRA ----- */

Quadra createQuadra(char *nome, double ancx, double ancy, double w, double h, char *corb, char *corp, char *sw);

/* ----- METODOS GET QUADRA ----- */

char* getNomeQuadra(Quadra q);

double getXQuadra(Quadra q);

double getYQuadra(Quadra q);

double getWQuadra(Quadra q);

double getHQuadra(Quadra q);

char* getCorbQuadra(Quadra q);

char* getCorpQuadra(Quadra q);

char* getSWQuadra(Quadra q);

/* ----- METODOS SET QUADRA ----- */

void setNomeQuadra(Quadra q, char *nome);

void setXQuadra(Quadra q, double x);

void setYQuadra(Quadra q, double y);

void setWQuadra(Quadra q, double w);

void setHQuadra(Quadra q, double h);

void setCorbQuadra(Quadra q, char *corb);

void setCorpQuadra(Quadra q, char *corp);

void setSWQuadra(Quadra q, char *sw);



/* ----- CONSTRUTOR RUA ----- */

Rua createRua(char *nome, char *lesq, char *ldir, double comp, double velocidade);

/* ----- METODOSO GET RUA ----- */

char* getNomeRUa(Rua r);

char* getLDIRRua(Rua r);

char* getLESQRua(Rua r);

double getComprimentoRua(Rua r);

double getVelocidadeRua(Rua r);

/* ----- METODOS SET RUA ----- */

void setNomeRUa(Rua r, char *nome);

void setLDIRRua(Rua r, char *ldir);

void setLESQRua(Rua r, char *lesq);

void setCompRua(Rua r, double comp);

void setVelocidadeRua(Rua r, double veloc);




/* ----- CONSTRUTOR ESQUINA ----- */

Esquina createEsquina(char *nome, double x, double y);


/* ----- METODOSO GET ESQUINA ----- */

char* getNomeEsquina(Esquina eq);

double getXEsquina(Esquina eq);

double getYEsquina(Esquina eq);


/* ----- METODOS SET ESQUINA ----- */

void setNomeEsquina(Esquina eq, char *nome);

void setXEsquina(Esquina eq, double x);

void setYEsquina(Esquina eq, double y);


/* ----- METODOS EXTRAS AUXILIARES ESQUINA ----- */

void calculaBoundingBoxEsquina(Esquina eq, double *x, double *y, double *w, double *h);


#endif