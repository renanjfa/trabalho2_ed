#ifndef TRATAR_STRINGS_H
#define TRATAR_STRINGS_H

#include <stdbool.h>

/*
    TRATAR_STRINGS.H:
    Modulo responsável por fazer o tratamento de strings e arquivos ao longo do projeto.
*/


/// @brief trata, concatena e formata corretamente a string de diretorio para entrada e saida
/// @param str string de argumento do path de saida ou entrada
/// @return retorna o diretorio/path corretamente formatado
char* trataDirEntrada(const char *str);

/// @brief concatena e conserta a string relacionada ao argumento .geo e a retorna ao main.
/// @param arqgeo nome e path do arquivo .geo.
/// @return retorna o nome para qual o .geo vai ser reconhecido.
char* getNomeGeo(const char *arqgeo);

/// @brief concatena e conserta a string relacionada ao argumento .qry e a retorna ao main.
/// @param arqqry nome e path do arquivo .qry.
/// @return retorna o nome para qual o .qry vai ser reconhecido.
char* getNomeQry(const char *arqry);

/// @brief concatena o nome do arquivo de saida unindo o nome do arquivo .geo e do nome do caso teste.
/// @param nomegeo string com nome do arquivo .geo.
/// @param nomeqry string com nome do arquivo .qry.
/// @return retorna a string concatenada do arquivo de saida.
char* concatenaNomeQry(const char* nomegeo, const char* nomeqry);

/// @brief concatena e conserta a string relacionada ao argumento .via e a retorna ao main.
/// @param arqvia nome e path do arquivo .via.
/// @return retorna o nome para qual o .via vai ser reconhecido.
char* getNomeVia(const char *arqvia);

/// @brief faz a leitura de uma linha do arquivo
/// @param arq arquivo a ser lido
/// @param linha string linha passada por referencia para receber toda a linha do arquivo
/// @param max_size tamanho maximo que a linha pode assumir
/// @return retorna true se a linha foi lida e associada, retorna false se chega ao fim do arquivo (linha vazia)
bool leituraLinha(FILE* arq, char *linha, int max_size);

#endif