#ifndef FUNCOESQRY_H
#define FUNCOESQRY_H

#include "graph.h"
#include "smutreap.h"
#include "lista.h"
#include "hash_table.h"

/*
    FUNCOESQRY.H
    Módulo responsável pelas funções componentes do arquivo .qry de consulta.
*/

/// @brief Salva em um registrador denominado "nomereg" de endereço na HashTable endereços, informações de nome, cep, face e num.
/// @param svg Arquivo svg usado para impressão de informações geradas. 
/// @param txt Arquivo txt usado para reportar informações geradas.
/// @param enderecos Tabela Hash responsável por armazenar registradores de endereços.
/// @param quadras Tabela Hash responsável por armazenar informações sobre as quadras de uma cidade para consulta.
/// @param nomereg Nome do registrador a ser criado.
/// @param cep Nome da quadra relacionada ao endereço.
/// @param face Face relacionada ao endereço (N, S, L, O).
/// @param num Numero realcionado ao endereço.
void registrarEndereco(FILE* svg, FILE* txt, HashTable enderecos, HashTable quadras, char *nomereg, char *cep, char face, int num);


/// @brief Alaga uma área determinada reconhecida pelo identificador n, as arestas nesta região são desabilitadas para uso até que ocorra a drenagem.
/// @param svg Arquivo svg usado para impressão de informações geradas.
/// @param txt Arquivo txt usado para reportar informações geradas.
/// @param g Grafo g correspondente ao sistema viário.
/// @param t SmuTreap t armazenando os vértices do grafo g. 
/// @param n Identificador da região n.
/// @param x Ancora x da região n determinada.
/// @param y Ancora y da região n determinada.
/// @param w Largura w da região n determinada.
/// @param h Altura h da região n determinada.
/// @param arestasN Vetor de listas de arestas armazenadas para consulta (Habilitar ou desabilitar arestasN).
void alag(FILE* svg, FILE* txt, Graph g, SmuTreap t, int n, double x, double y, double w, double h, Lista *arestasN);


/// @brief Drena uma área determinada reconhecida pelo identificador n, as arestas são desabilitadas reabilitando seu uso.
/// @param txt Arquivo txt usado para reportar informações geradas.
/// @param g Grafo g correspondente ao sistema viário. 
/// @param n Identificador da região n.
/// @param arestasN Vetor de listas de arestas armazenadas para consulta (Habilitar ou desabilitar arestasN).
void dren(FILE* txt, Graph g, int n, Lista *arestasN);


/// @brief Cria um subgrafo interno ao Grafo g que determina o grafo induzido dos vértices internos a uma região determinada.
/// @param svg Arquivo svg usado para impressão de informações geradas.
/// @param g Grafo g correspondente ao sistema viário.
/// @param t SmuTreap t armazenando os vértices do grafo g.
/// @param nome Nome ao qual o subgrafo deve ser chamado.
/// @param x Ancora x da região determinada.
/// @param y Ancora y da região determinada.
/// @param w Largura w da região determinada.
/// @param h Altura h da região determinada.
void sg(FILE* svg, Graph g, SmuTreap t, char *nome, double x, double y, double w, double h);


/// @brief Salva em um registrador de percurso o caminho mínimo entre o registrador de origem e destino.
/// @param txt Arquivo txt usado para reportar informações geradas.
/// @param g Grafo g correspondente ao sistema viário.
/// @param t SmuTreap t armazenando os vértices do grafo g.
/// @param enderecos Tabela Hash responsável por armazenar registradores de endereços.
/// @param percursos Tabela Hash reponsável por armazenar os registradores de percurso.
/// @param np Nome que deverá ser associado ao percurso. 
/// @param nome Nome do subgrafo a ser realizado a pesquisa de caminho mínimo.
/// @param reg1 Nome do registrador de origem.
/// @param reg2 Nome do registrador de destino.
void registrarPercurso(FILE* txt, Graph g, SmuTreap t, HashTable enderecos, HashTable percursos, char *np, char *nome, char *reg1, char *reg2);


/// @brief Salva em um registrador de percurso o caminho mínimo entre o final do primeiro percurso e o início do segundo percurso.
/// @param txt Arquivo txt usado para reportar informações geradas.
/// @param g Grafo g correspondente ao sistema viário.
/// @param t SmuTreap t armazenando os vértices do grafo g.
/// @param percursos Tabela Hash reponsável por armazenar os registradores de percurso.
/// @param np Nome que deverá ser associado ao percurso.
/// @param np1 Nome do primeiro percurso a ser unido.
/// @param np2 Nome do segundo percurso a ser unido.
void join(FILE* txt, Graph g, SmuTreap t, HashTable percursos, char *np, char *np1, char *np2);


/// @brief Mostra no arquivo svg fornecido o caminho mais curto e o caminho mais rápido do percurso np.
/// @param svg Arquivo svg usado para impressão de informações geradas.
/// @param np Nome do percurso animado a ser mostrado no svg.
/// @param cmc Cor que deverá ser mostrado o caminho mais curto do percurso.
/// @param cmr Cor que deverá ser mostrado o caminho mais rápido do percurso.
/// @param percursos Tabela Hash reponsável por armazenar os registradores de percurso.
void shw(FILE* svg, char *np, char *cmc, char *cmr, HashTable percursos);


#endif