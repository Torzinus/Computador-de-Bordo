#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "escalonador.h"

int abrirEntrada(char * entrada, int * tempo_total, Tarefa * t, int * n){
    //abrindo o arquivo:
    FILE * arquivo = fopen(entrada, "r");
    if(arquivo == NULL){
        fprintf(stderr, "Falha ao abrir o arquivo %s\n", entrada);
        return 1;
    }
    
    //lendo as linhas do arquivo:
    fscanf(arquivo, "%d", tempo_total);
    *n = 0;

    while(fscanf(arquivo, "%s %d %d %d", t[*n].nome, &t[*n].periodo, &t[*n].deadline, &t[*n].burst) == 4){
        (*n)++;
    }
    fclose(arquivo);
    return 0;
}

FILE * abrirSaida(char * escalonador){
    FILE * output;
    if(strcmp(escalonador, "rate") == 0){
        output = fopen("rate_hcs4.out", "w");
    } else{
        output = fopen("edf_hcs4.out", "w");
    }
    return output;
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

    if (abrirEntrada(entrada, &tempo_total, t, &n) != 0){
        free(t);
        free(cont);
        return 1;
    }

    char (*rodou)[100] = malloc(tempo_total * sizeof(char[100]));
    char * situacao = malloc(tempo_total * sizeof(char));

    for(int i = 0; i < n; i++){ //inicializa a contagem para cada tarefa(começando do zero)
        cont[i].complete = 0;
        cont[i].lost = 0;
        cont[i].killed = 0;
    }
    
    FILE * output = abrirSaida(algoritmo);
    if (output == NULL){
        free(t);
        free(cont);
        free(rodou);
        free(situacao);
        return 1;
    }
    simulacao(t, cont, n, tempo_total, algoritmo, rodou, situacao);
    
    if (strcmp(algoritmo, "rate") == 0) {
        fprintf(output, "EXECUTION BY RATE\n\n");
    } else {
    fprintf(output, "EXECUTION BY EDF\n\n");
    }
    
    gerarLog(rodou, tempo_total, output, situacao);
    escreverResumo(t, cont, n, output);
    fclose(output);

    free(t);
    free(cont);
    free(rodou);
    free(situacao);

    return 0;
}