#define ESCALONADOR_H

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

void simulacao(Tarefa * t, Contagem * cont, int n, int tempo_total, char * escalonador);