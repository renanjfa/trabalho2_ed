#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hash_table.h"
#include "leitura_cidade.h"
#include "leitura_via.h"
#include "leitura_qry.h"
#include "graph.h"
#include "tratar_strings.h"


int main(int argc, char* argv[]) {
    // criacao de strings para dirEntrada, dirSaida, arquivoGeo, arquivoQry, arquivoVia
    char *dirEntrada = NULL, *arquivoGeo = NULL, *arquivoVia = NULL, *arquivoQry = NULL, *dirSaida = NULL; 

    bool existegeo = false, existevia = false, existeqry = false;

    // loop para leitura dos parametros
    for(int i = 1; i < argc; i++) {

        if(strcmp(argv[i], "-e") == 0) {
            dirEntrada = trataDirEntrada(argv[i+1]);
            existegeo = true;
        }

        else if(strcmp(argv[i], "-f") == 0) {
            arquivoGeo = (char*)malloc(sizeof(char)*(strlen(argv[i + 1]) + 5));
            if(arquivoGeo == NULL){
                printf("Erro na alocação de memória da string!\n");
                exit(1);
            }
            strcpy(arquivoGeo, argv[i + 1]);
        }

        else if(strcmp(argv[i], "-q") == 0) {
            arquivoQry = (char*)malloc(sizeof(char)*(strlen(argv[i + 1]) + 5));
            if(arquivoQry == NULL){
                printf("Erro na alocação de memória da string!\n");
                exit(1);
            }
            strcpy(arquivoQry, argv[i + 1]);
            existeqry = true;
        }

        else if(strcmp(argv[i], "-v") == 0) {
            arquivoVia = (char*)malloc(sizeof(char)*(strlen(argv[i + 1]) + 5));
            if(arquivoVia == NULL){
                printf("Erro na alocação de memória da string!\n");
                exit(1);
            }
            strcpy(arquivoVia, argv[i + 1]);
            existevia = true;
        }

        else if (strcmp(argv[i], "-o") == 0 ) {
            dirSaida = trataDirEntrada(argv[i+1]);
        }
    }

    // processa geo
    char *nomegeo = getNomeGeo(arquivoGeo);
    HashTable quadras;

    if(existegeo) {
        char *entradageo = (char*)malloc(sizeof(char)*(strlen(dirEntrada)+strlen(arquivoGeo)+2));
        if(!entradageo) exit(1);
        entradageo[0] = '\0';
        strcat(entradageo, dirEntrada);
        strcat(entradageo, arquivoGeo);

        quadras = ProcessaCidade(entradageo, dirSaida, nomegeo);
    } else {
        quadras = ProcessaCidade(arquivoGeo, dirSaida, nomegeo);
    }

    // processa via
    char *nomevia = getNomeVia(arquivoVia);
    Graph g;
    SmuTreap smuVertices = newSmuTreap(100, 1, 0.00001, 100000);

    if(existevia) {
        char *entradavia = (char*)malloc(sizeof(char)*(strlen(dirEntrada)+strlen(arquivoQry)+2));
        if(!entradavia) exit(1);
        entradavia[0] = '\0';
        strcat(entradavia, dirEntrada);
        strcat(entradavia, arquivoVia);
        g = ProcessaVia(entradavia, smuVertices);
    } else {
        g = ProcessaVia(arquivoVia, smuVertices);
    }

    // inicializacao de registradores de endereco, percurso e regioes de arestasN
    HashTable enderecos = createHashTable(20);
    HashTable percursos = createHashTable(20);

    Lista *arestasN = malloc(100*sizeof(Lista));
    for(int i = 0; i<100; i++) {
        arestasN[i] = criaLista();
    }


    // processa qry 
    if(existeqry) {
        char* nomearqsaida = concatenaNomeQry(nomegeo, getNomeQry(arquivoQry));
        ProcessaQry(dirEntrada, dirSaida, nomearqsaida, arquivoQry, g, smuVertices, quadras, enderecos, percursos, arestasN);
    }

    killSmuTreap(smuVertices);
    killDG(g);
    destroiHashTable(percursos);
    destroiHashTable(enderecos);
    destroiHashTable(quadras);
    for(int i = 0; i<100; i++) {
        liberaLista(arestasN[i]);
    }
}

/*
    <--- ESTRUTURAS UTILIZADAS NO TRABALHO --->

    HashTable<Quadras> quadras;      (dicionario para consulta de nomeQuadra->quadra)
    Graph g;                         (Grafo guardando os vertices representando a via)
    SmuTreap smuVertices;            (SmuTreap para vertices do grafo, busca espacial em regiao)
    HashTable<Enderecos> enderecos;  (dicionario para consulta de nomeReg->endereco) tam = 11
    HashTable<Percursos> percursos;  (dicionario para consulta de nomePerc->percurso) tam = 15
    Lista *arestasN;                 (Vetor de listas de Edges) tam = 100;

*/ 
