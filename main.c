#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "escalonador.h"

void abrirArquivo(char * entrada, int * tempo_total, Tarefa * t, int * n){
    //abrindo o arquivo:
    FILE * arquivo = fopen(entrada, "r");
    if(arquivo == NULL){
        fprintf(stderr, "Falha ao abrir o arquivo %s\n", entrada);
        return;
    }
    
    //lendo as linhas do arquivo:
    fscanf(arquivo, "%d", tempo_total);
    *n = 0;

    while(fscanf(arquivo, "%s %d %d %d", t[*n].nome, &t[*n].periodo, &t[*n].deadline, &t[*n].burst) == 4){
        (*n)++;
    }
    fclose(arquivo);
}

int main(int argc, char * argv[]){
    if(argc != 3){
        fprintf(stderr, "O programa precisa de exatamente 2 argumentos\n");
        return 1;
    }
    
    char * algoritmo = argv[1];
    char * entrada = argv[2];

    if(strcmp(algoritmo, "rate") != 0 && strcmp(algoritmo, "edf") != 0){
        fprintf(stderr, "O escalonador deve ser 'rate' ou 'edf'\n");
        return 1;
    }

    int tempo_total;
    Tarefa * t = malloc(100 * sizeof(Tarefa));
    Contagem * cont = malloc(100 * sizeof(Contagem));
    int n;

    for(int i = 0; i < n; i++){ //inicializa a contagem para cada tarefa(começando do zero)
        cont[i].complete = 0;
        cont[i].lost = 0;
        cont[i].killed = 0;
    }

    abrirArquivo(entrada, &tempo_total, t, &n);

    simulacao(t, cont, n, tempo_total, algoritmo);
    //mudar essa saída depois:
    for(int i = 0; i < n; i++){
        printf("[%s]\nCOMPLETE: %d\nLOST: %d\nKILLED: %d\n\n", t[i].nome, cont[i].complete, cont[i].lost, cont[i].killed);
    }

    free(t);
    free(cont);

    return 0;
}