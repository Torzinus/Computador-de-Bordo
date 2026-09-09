#define ESCALONADOR_H

#include <stdio.h>

typedef struct Tarefa{
    char nome[100];
    int periodo;
    int deadline;
    int burst;

    int prox_chegada;
    int deadline_restante;
    int burst_restante;
    int estado; //0 - waiting, 1 - ready, 2 - dead
} Tarefa;

typedef struct Contagem{ 
    int complete;
    int lost;
    int killed;
} Contagem;

void simulacao(Tarefa * t, Contagem * cont, int n, int tempo_total, char * algoritmo, char rodou[][100], char * situacao);
void gerarLog(char rodou[][100], int tempo_total, FILE * output, char * situacao);
void escreverResumo(Tarefa *t, Contagem *cont, int n, FILE *output);