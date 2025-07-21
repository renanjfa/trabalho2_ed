#ifndef LINHA_H
#define LINHA_H

typedef void *Linha;
/*
    LINHA.H
    Módulo responsável por gerenciar a forma de uma linha, incluindo operacoes de set e get e calculo de area da forma.
*/


/* ----- CONSTRUTOR DA FORMA LINHA ----- */

/// @brief cria e retorna uma forma linha com suas informações básicas
/// @param i identificador da linha
/// @param x1 coordenada x do primeiro ponto
/// @param y1 coordenada y do primeiro ponto
/// @param x2 coordenada x do segundo ponto
/// @param y2 coordenada y do segundo ponto
/// @param cor cor da linha
/// @return retorna a linha
Linha criarLinha(int i, double x1, double y1, double x2, double y2, char *cor, bool pontilhada);




/* ----- METODOS GET LINHA ----- */

/// @brief método get do identificador da linha
/// @param l Linha l
/// @return retorna o identificador i
int getILinha(Linha l);


/// @brief método get da coordenada x do primeiro ponto da linha
/// @param l Linha l
/// @return retorna a coordenada x1
double getX1Linha(Linha l);


/// @brief método get da coordenada y do primeiro ponto da linha
/// @param l Linha l
/// @return retorna a coordenada y1
double getY1Linha(Linha l);


/// @brief método get da coordenada x do segundo ponto da linha
/// @param l Linha l
/// @return retorna a coordenada x2
double getX2Linha(Linha l);


/// @brief método get da coordenada y do segundo ponto da linha
/// @param l Linha l
/// @return retorna a coordenada y2
double getY2Linha(Linha l); 
    

/// @brief método get da cor da linha
/// @param l Linha l
/// @return retorna a cor
char* getCorLinha(Linha l); 


/// @brief método get da largura do traço da linha
/// @param l Linha l
/// @return retorna a largura do traço (stroke-width)
double getSWLinha(Linha l);

/// @brief metodo get para verificacao se a linha é pontilhada ou não
/// @param l Linha l
/// @return retorna a flag de pontilhado
bool getPontilhadaLinha(Linha l);




/* ----- METODOS SET LINHA ----- */

/// @brief método set do identificador da linha
/// @param l Linha l
/// @param i novo identificador i
void setILinha(Linha l, int i);


/// @brief método set da coordenada x do primeiro ponto da linha
/// @param l Linha l
/// @param x nova coordenada x1
void setX1Linha(Linha l, double x);


/// @brief método set da coordenada y do primeiro ponto da linha
/// @param l Linha l
/// @param y nova coordenada y1
void setY1Linha(Linha l, double y); 


/// @brief método set da coordenada x do segundo ponto da linha
/// @param l Linha l
/// @param x nova coordenada x2
void setX2Linha(Linha l, double x);


/// @brief método set da coordenada y do segundo ponto da linha
/// @param l Linha l
/// @param y nova coordenada y2
void setY2Linha(Linha l, double y);


/// @brief método set da cor da linha
/// @param l Linha l
/// @param cor nova cor da linha
void setCorLinha(Linha l, char* cor);


/// @brief método set da largura do traço da linha
/// @param l Linha l
/// @param sw nova largura do traço
void setSWLinha(Linha l, double sw);



/* ----- FUNCOES ADICIONAIS ----- */
        
/// @brief calcula a área associada à linha
/// @param l Linha l
/// @return retorna a área
double calculaAreaL(Linha l);


#endif