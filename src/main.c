#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "leitura_cidade.h"
#include "leitura_via.h"
#include "graph.h"

int main(int argc, char* argv[]) {
    // criacao de strings para dirEntrada, dirSaida, arquivoGeo, arquivoQry, arquivoVia
    
    // loop para leitura dos parametros
    
    // processa geo
        // leitura geo e colocar quadras na smutreap??

    HashTable quadras = ProcessaCidade("pathcidade", "dirsaida", "nomecidade");

    // processa via
        // leitura via e inserir em graph
    SmuTreap smuVertices = newSmuTreap(100, 1.5, 0.000001, 100000);
    Graph via = ProcessaVia("pathvia", smuVertices);


    // inicializacao de registradores de endereco, percurso

    // processa qry 
        // leitura e operacoes

}