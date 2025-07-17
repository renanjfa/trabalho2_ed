#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "strings.h"

char* trataDirEntrada(const char* str) {
    
    size_t len = strlen(str);
    char* dir = (char*)malloc(sizeof(char)*(len + 1));
    if(dir==NULL){
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }
    strcpy(dir, str);

    if (dir[len - 1] != '/') {
        //dir[len] = '/';
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
    
    char* nomegeo = (char*)malloc(sizeof(char)*(len + 1));
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
    
    char* nomvia = (char*)malloc(sizeof(char)*(len + 1));
    if (nomvia == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        nomvia[i] = nomeInicio[i];
    }
    nomvia[len] = '\0';

    return nomvia;
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
    char* nomeqry = (char*)malloc(sizeof(char)*(tamanho + 1)); 
    if (nomeqry == NULL) {
        printf("Erro na alocação de memória da string!\n");
        exit(1);
    }

    
    strncpy(nomeqry, nomeInicio, tamanho);
    nomeqry[tamanho] = '\0'; 

    return nomeqry;
}

char* concatenaNomeQry(const char* nomegeo, const char* nomeqry) {
    size_t tamanho = strlen(nomegeo) + strlen(nomeqry) + 2; 
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