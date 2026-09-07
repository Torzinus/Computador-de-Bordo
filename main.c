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
    
    char * modo = argv[1];
    char * entrada = argv[2];

    if(strcmp(modo, "rate") != 0 && strcmp(modo, "edf") != 0){
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

    //só pra testar:
    printf("Tempo total: %d\n", tempo_total);
    printf("Qtd de tarefas: %d\n", n);
    printf("Nome: %s\nPeríodo: %d\nDeadline: %d\nBurst: %d\n", t[0].nome, t[0].periodo, t[0].deadline, t[0].burst);
    printf("Nome: %s\nPeríodo: %d\nDeadline: %d\nBurst: %d\n", t[1].nome, t[1].periodo, t[1].deadline, t[1].burst);

    //inserir função da simulação aqui embaixo:

    free(t);

    return 0;
}