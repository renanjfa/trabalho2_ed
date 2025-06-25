#ifndef CIRCULO_H
#define CIRCULO_H

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef void *Circulo; 
/*
    Arquivo .h relacionado a uma forma de um circulo, incluindo operacoes de set e get e calculo de area da forma.
*/



/* ----- CONSTRUTOR CIRCULO ----- */

/// @brief Cria e retorna um novo círculo com os atributos fornecidos.
/// @param i Identificador do círculo
/// @param x Coordenada X do centro do círculo
/// @param y Coordenada Y do centro do círculo
/// @param raio Raio do círculo
/// @param corb Cor da borda do círculo
/// @param corp Cor de preenchimento do círculo
/// @return Retorna o círculo criado
Circulo criarCirculo(int i, double x, double y, double raio, char *corb, char *corp);



/* ----- METODOS GET CIRCULO ----- */

/// @brief Retorna o identificador do círculo
/// @param c Círculo
/// @return Identificador do círculo
int getICirculo(Circulo c);


/// @brief Retorna a coordenada X do centro do círculo
/// @param c Círculo
/// @return Coordenada X
double getXCirculo(Circulo c);


/// @brief Retorna a coordenada Y do centro do círculo
/// @param c Círculo
/// @return Coordenada Y
double getYCirculo(Circulo c);


/// @brief Retorna o raio do círculo
/// @param c Círculo
/// @return Raio
double getRCirculo(Circulo c);


/// @brief Retorna a cor da borda do círculo
/// @param c Círculo
/// @return Cor da borda (string)
char* getCorbCirculo(Circulo c);


/// @brief Retorna a cor de preenchimento do círculo
/// @param c Círculo
/// @return Cor de preenchimento (string)
char* getCorpCirculo(Circulo c);


/// @brief Retorna a espessura da borda (stroke-width) do círculo
/// @param c Círculo
/// @return Espessura da borda
double getSWCirculo(Circulo c);



/* ----- METODOS SET CIRCULO ----- */

/// @brief Define o identificador do círculo
/// @param c Círculo
/// @param i Novo identificador
void setICirculo(Circulo c, int i);


/// @brief Define a coordenada X do centro do círculo
/// @param c Círculo
/// @param x Nova coordenada X
void setXCirculo(Circulo c, double x);


/// @brief Define a coordenada Y do centro do círculo
/// @param c Círculo
/// @param y Nova coordenada Y
void setYCirculo(Circulo c, double y);


/// @brief Define o raio do círculo
/// @param c Círculo
/// @param r Novo raio
void setRCirculo(Circulo c, double r);


/// @brief Define a cor da borda do círculo
/// @param c Círculo
/// @param corb Nova cor da borda (string)
void setCorbCirculo(Circulo c, char* corb);


/// @brief Define a cor de preenchimento do círculo
/// @param c Círculo
/// @param corp Nova cor de preenchimento (string)
void setCorpCirculo(Circulo c, char* corp);


/// @brief Define a espessura da borda (stroke-width) do círculo
/// @param c Círculo
/// @param sw Nova espessura da borda
void setSWCirculo(Circulo c, double sw);




/* ----- FUNCOES ADICIONAIS ----- */

/// @brief Calcula e retorna a área do círculo
/// @param c Círculo
/// @return Área do círculo
double calculaAreaC(Circulo c);


#endif