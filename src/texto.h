#ifndef TEXTO_H
#define TEXTO_H

typedef void *Texto;
typedef void *Estilo;
/*
    Arquivo .h relacionado a uma forma de um texto, incluindo operacoes de set e get e calculo de area da forma.
*/


/* ----- CONSTRUTOR ESTILO DE TEXTO ----- */

/// @brief cria e retorna um estilo que vai ser associado a uma forma texto
/// @param family familia da fonte
/// @param weight weight da fonte
/// @param size tamanho da fonte
/// @return retorna o estilo
Estilo criarEstilo(char *family, char *weight, char *size);



/* ----- METODOS GET ESTILO ----- */

/// @brief metodo get da familia da fonte  do texto 
/// @param ts Estilo ts
/// @return retorna a familia
char* getFamily(Estilo ts);


/// @brief metodo get do weight da fonte do texto 
/// @param ts Estilo ts
/// @return retorna o weight
char* getWeight(Estilo ts);


/// @brief metodo get do tamanho da fonte do texto
/// @param ts Estilo ts
/// @return retorna o tamanho da fonte
char* getSize(Estilo ts);




/* ----- METODOS SET ESTILO ----- */

/// @brief metodo set da familia da fonte do texto 
/// @param ts Estilo ts
/// @param family nova familia da fonte
void setFamily(Estilo ts, char *family); 


/// @brief metodo set do weight da fonte do texto
/// @param ts Estilo ts
/// @param weight novo weight da fonte
void setWeight(Estilo ts, char *weight);


/// @brief metodo set do tamanho da fonte do texto
/// @param ts Estilo ts
/// @param size novo tamanho de fonte
void setSize(Estilo ts, char *size);




/* ----- CONSTRUTOR DA FORMA TEXTO ----- */

/// @brief cria e retorna uma forma texto que contem informacoes variadas
/// @param i identificador id
/// @param x ancora x
/// @param y ancora y
/// @param corb cor da borda
/// @param corp cor de preenchimento
/// @param a identificador de posicao relativa a (meio, inicio, fim)
/// @param texto texto associado a forma texto
/// @param ts estilo ts
/// @return retorna o texto
Texto criarTexto(int i, double x, double y, char *corb, char *corp, char a, char *texto, Estilo ts);




/* ----- METODOS GET TEXTO ----- */

/// @brief metodo get do identificador do texto
/// @param t Texto t
/// @return retorna o id
int getITexto(Texto t);


/// @brief metodo get da ancora x do texto
/// @param t Texto t
/// @return retorna a ancora x
double getXTexto(Texto t); 


/// @brief metodo get da ancora y do texto
/// @param t Texto t
/// @return retorna a ancora y
double getYTexto(Texto t); 


/// @brief metodo get da cor da borda do texto
/// @param t Texto t
/// @return retorna a cor da borda
char* getCorbTexto(Texto t); 


/// @brief metodo get da cor de preenchimento do texto
/// @param t Texto t
/// @return retorna a cor de preenchimento
char* getCorpTexto(Texto t); 


/// @brief metodo get do a (posicao relativa do texto meio, fim, inicio) do texto
/// @param t Texto t
/// @return retorna a
char getATexto(Texto t);


/// @brief metodo get do texto relacionado ao texto 
/// @param t Texto t
/// @return retorna o texto 
char* getTextTexto(Texto t); 


/// @brief metodo get da largura da borda do texto
/// @param t Texto t
/// @return retorna a largura da borda do texto
double getSWTexto(Texto t);


/// @brief metodo get do estilo do texto
/// @param t Texto t
/// @return retorna o estilo associado ao texto
Estilo getStyle(Texto t);




/* ----- METODOS SET TEXTO ----- */

/// @brief metodo set do identificador id do texto
/// @param t Texto t
/// @param i novo identificador 
void setITexto(Texto t, int i); 


/// @brief metodo set para a ancora x do texto
/// @param t Texto t
/// @param x nova coordenada x
void setXTexto(Texto t, double x); 


/// @brief metodo set para a ancora y do texto
/// @param t Texto t
/// @param y nova coordenada y
void setYTexto(Texto t, double y); 


/// @brief metodo set da cor da borda do texto 
/// @param t Texto t
/// @param corb nova cor da borda
void setCorbTexto(Texto t, char *corb); 


/// @brief metodo set da cor de preenchimento do texto 
/// @param t Texto t
/// @param corp nova cor de preenchimento
void setCorpTexto(Texto t, char *corp);


/// @brief metodo set do texto relacionado a forma texto
/// @param t Texto t
/// @param texto novo texto 
void setTextTexto(Texto t, char *texto); 

/// @brief metodo set da largura da borda do texto
/// @param t Texto t
/// @param sw nova largura da borda sw
void setSWTexto(Texto t, double sw);



/* ----- FUNCOES ADICIONAIS ----- */


/// @brief calcula a area relacionada ao texto
/// @param t Texto t
/// @return retorna a area
double calculaAreaT(Texto t);


#endif