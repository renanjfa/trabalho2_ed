#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tratar_strings.h"

char* trataDirEntrada(const char* str) {
    
    size_t len = strlen(str);
    char* dir = (char*)malloc(sizeof(char)*(len + 3));
    if(dir==NULL){
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }
    strcpy(dir, str);

    if (dir[len - 1] != '/') {
        dir[len] = '\0'; 
    }

    strcat(dir, "/\0");
    return dir;
}

char* getNomeGeo(const char* arqgeo) {
    
    const char* nomeInicio = strrchr(arqgeo, '/');
    if (!nomeInicio) {
        nomeInicio = arqgeo; 
    } else {
        nomeInicio++; 
    }

    int len = 0;
    while (nomeInicio[len] != '.' && nomeInicio[len] != '\0') {
        len++;
    }
    
    char* nomegeo = (char*)malloc(sizeof(char)*(len + 3));
    if (nomegeo == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        nomegeo[i] = nomeInicio[i];
    }
    nomegeo[len] = '\0';

    return nomegeo;
}

char* getNomeVia(const char* arqvia) {
    
    const char* nomeInicio = strrchr(arqvia, '/');
    if (!nomeInicio) {
        nomeInicio = arqvia; 
    } else {
        nomeInicio++; 
    }

    int len = 0;
    while (nomeInicio[len] != '.' && nomeInicio[len] != '\0') {
        len++;
    }
    
    char* nomevia = (char*)malloc(sizeof(char)*(len + 3));
    if (nomevia == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        nomevia[i] = nomeInicio[i];
    }
    nomevia[len] = '\0';

    return nomevia;
}

char* getNomeQry(const char* arqqry) {
   
    const char* nomeInicio = strrchr(arqqry, '/');
    if (!nomeInicio) {
        nomeInicio = arqqry;
    } else {
        nomeInicio++; 
    }
 
   
    const char* ponto = strrchr(nomeInicio, '.');
    if (!ponto) {
        printf("Erro: Nome do arquivo não contém extensão!\n");
        exit(1);
    }

    
    size_t tamanho = ponto - nomeInicio;
    char* nomeqry = (char*)malloc(sizeof(char)*(tamanho + 3)); 
    if (nomeqry == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }

    
    strncpy(nomeqry, nomeInicio, tamanho);
    nomeqry[tamanho] = '\0'; 

    return nomeqry;
}

char* concatenaNomeQry(const char* nomegeo, const char* nomeqry) {
    size_t tamanho = strlen(nomegeo) + strlen(nomeqry) + 3; 
    char* concatnome = (char*)malloc(sizeof(char)*tamanho);

    if (concatnome == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }

    concatnome[0] = '\0';

    strcat(concatnome, nomegeo);
    strcat(concatnome, "-");
    strcat(concatnome, nomeqry);
    return concatnome;
}

bool leituraLinha(FILE* arq, char *linha, int max_size) {
    if (!arq || !linha) return false;

    if (fgets(linha, max_size, arq) == NULL) {
        if (feof(arq)) return false; 
        if (ferror(arq)) {
            perror("[ERRO] na leitura do arquivo");
            exit(1); 
        }
        return false;
    }

    linha[strcspn(linha, "\r\n")] = '\0';
    return true;
}