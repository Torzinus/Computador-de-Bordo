#include "escalonador.h"

void simulacao(Tarefa * t, Contagem * cont, int n, int tempo_total, char * escalonador){
    for(int i = 0; i < n; i ++){    //prepara o estado inicial para cada tarefa
        t[i].prox_chegada = t[i].periodo;
        t[i].deadline_restante = t[i].deadline;   //tempo até o prazo(deadline) da tarefa acabar
        t[i].burst_restante = t[i].burst;   //tempo até o burst da tarefa acabar
        t[i].estado = 1;    //estado ready(pronto)
    }
    for (int tempo = 0; tempo < tempo_total; tempo++){
        //blablabla
    }
}