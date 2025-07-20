#ifndef RETANGULO_H
#define RETANGULO_H

#include "stdbool.h"

typedef void *Retangulo; 
/*
    Arquivo .h relacionado a uma forma de um retangulo, incluindo operacoes de set e get e calculo de area da forma.
*/



/* ----- CONSTRUTOR DA FORMA RETANGULO ----- */

/// @brief cria e retorna uma forma retângulo com suas informações básicas
/// @param i identificador do retângulo
/// @param x coordenada x da âncora
/// @param y coordenada y da âncora
/// @param w largura do retângulo
/// @param h altura do retângulo
/// @param corb cor da borda
/// @param corp cor de preenchimento
/// @return retorna o retângulo
Retangulo criarRetangulo(int i, double x, double y, double w, double h, char *corb, char *corp);




/* ----- METODOS GET RETANGULO ----- */

/// @brief método get do identificador do retângulo
/// @param r Retangulo r
/// @return retorna o identificador i
int getIRetangulo(Retangulo r);


/// @brief método get da coordenada x da âncora do retângulo
/// @param r Retangulo r
/// @return retorna a coordenada x
double getXRetangulo(Retangulo r);
    

/// @brief método get da coordenada y da âncora do retângulo
/// @param r Retangulo r
/// @return retorna a coordenada y
double getYRetangulo(Retangulo r); 


/// @brief método get da largura do retângulo
/// @param r Retangulo r
/// @return retorna a largura w
double getWRetangulo(Retangulo r); 


/// @brief método get da altura do retângulo
/// @param r Retangulo r
/// @return retorna a altura h
double getHRetangulo(Retangulo r); 
    

/// @brief método get da cor da borda do retângulo
/// @param r Retangulo r
/// @return retorna a cor da borda
char* getCorbRetangulo(Retangulo r); 
    

/// @brief método get da cor de preenchimento do retângulo
/// @param r Retangulo r
/// @return retorna a cor de preenchimento
char* getCorpRetangulo(Retangulo r); 
    

/// @brief método get da largura do traço (stroke-width) do retângulo
/// @param r Retangulo r
/// @return retorna a largura do traço
double getSWRetangulo(Retangulo r);




/* ----- METODOS SET RETANGULO ----- */

/// @brief método set do identificador do retângulo
/// @param r Retangulo r
/// @param i novo identificador i
void setIRetangulo(Retangulo r, int i);


/// @brief método set da coordenada x da âncora do retângulo
/// @param r Retangulo r
/// @param x nova coordenada x
void setXRetangulo(Retangulo r, double x);


/// @brief método set da coordenada y da âncora do retângulo
/// @param r Retangulo r
/// @param y nova coordenada y
void setYRetangulo(Retangulo r, double y);


/// @brief método set da largura do retângulo
/// @param r Retangulo r
/// @param w nova largura w
void setWRetangulo(Retangulo r, double w);


/// @brief método set da altura do retângulo
/// @param r Retangulo r
/// @param h nova altura h
void setHRetangulo(Retangulo r, double h);


/// @brief método set da cor da borda do retângulo
/// @param r Retangulo r
/// @param corb nova cor da borda
void setCorbRetangulo(Retangulo r, char* corb);


/// @brief método set da cor de preenchimento do retângulo
/// @param r Retangulo r
/// @param corp nova cor de preenchimento
void setCorpRetangulo(Retangulo r, char* corp);


/// @brief método set da largura do traço (stroke-width) do retângulo
/// @param r Retangulo r
/// @param sw nova largura do traço
void setSWRetangulo(Retangulo r, double sw);





/* ----- FUNCOES ADICIONAIS ----- */

/// @brief calcula a área do retângulo
/// @param r Retangulo r
/// @return retorna a área
double calculaAreaR(Retangulo r); 
    

#endif