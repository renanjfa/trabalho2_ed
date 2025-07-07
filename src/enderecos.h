#ifndef ENDERECOS_H
#define ENDERECOS_H

typedef void *Rua;  // nome, ldir, lesq, comp, velocidade
typedef void *Quadra;   // nome, cep (nome, direcao, ), ancora x, y
typedef void *Endereco;
// colocar as quadras em uma hashtable para consulta posterior


/* ----- CONSTRUTOR QUADRA ----- */

Quadra createQuadra(char *nome, double ancx, double ancy, double w, double h);

/* ----- METODOS GET QUADRA ----- */

char* getNomeQuadra(Quadra q);

double getXQuadra(Quadra q);

double getYQuadra(Quadra q);

double getWQuadra(Quadra q);

double getHQuadra(Quadra q);


/* ----- METODOS SET QUADRA ----- */

void setNomeQuadra(Quadra q, char *nome);

void setXQuadra(Quadra q, double x);

void setYQuadra(Quadra q, double y);

void setWQuadra(Quadra q, double w);

void setHQuadra(Quadra q, double h);



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


#endif