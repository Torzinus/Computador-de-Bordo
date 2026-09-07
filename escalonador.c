#include "escalonador.h"
#include <string.h>

void simulacao(Tarefa * t, Contagem * cont, int n, int tempo_total, char * algoritmo){
    for(int i = 0; i < n; i ++){    //prepara o estado inicial para cada tarefa
        t[i].prox_chegada = t[i].periodo;
        t[i].deadline_restante = t[i].deadline;   //tempo até o prazo(deadline) da tarefa acabar
        t[i].burst_restante = t[i].burst;   //tempo até o burst da tarefa acabar
        t[i].estado = 1;    //estado ready(pronto)
    }
    for (int tempo = 0; tempo < tempo_total; tempo++){  //loop da execução das tarefas
        //verificando se uma nova instância aparaceu:
        for(int i = 0; i < n; i ++){
            if(t[i].prox_chegada == tempo){
                t[i].estado = 1;
                t[i].burst_restante = t[i].burst;
                t[i].deadline_restante = t[i].deadline;
                t[i].prox_chegada += t[i].periodo;  //agenda a próxima chegada da nova instância
            }
        }
        //verificando se chegou no deadline e o prazo acabou
        for(int i = 0; i < n; i ++){
            if (t[i].estado == 1){
                t[i].deadline_restante --;
                if(t[i].deadline_restante == 0){    //se a tarefa não concluiu dentro do prazo:
                    t[i].estado = 2;    
                    cont[i].lost ++;    //o processo encerra e é dado como lost
                }
            }
        }
        //escolhendo qual tarefa devemos executar
        int escolhida;
        int tem_escolhida = 0;

        for(int i = 0; i < n; i ++){
            if(t[i].estado == 1){    //a tarefa precisa estar pronta
                if(tem_escolhida == 0){
                    escolhida = i;
                    tem_escolhida = 1;
                }
            }
            if(tem_escolhida == 1){
                if(strcmp(algoritmo, "rate") == 0){
                    if(t[i].periodo < t[escolhida].periodo){    //quanto menor o período, maior a prioridade
                        escolhida = i;
                    }
                }
                if(strcmp(algoritmo, "edf") == 0){
                    if(t[i].deadline_restante < t[escolhida].deadline_restante){    //quanto menor o deadline, maior a prioridade
                        escolhida = i;
                    }
                }
            }
        }
        //executando a instancia escolhida:
        if(tem_escolhida == 1){
            t[escolhida].burst_restante --;
            if(t[escolhida].burst_restante == 0){   //se acabou o burst, a instancia foi concluída
                t[escolhida].estado = 0;
                cont[escolhida].complete ++;    //fica em espera e é dada como complete
            }
        }
    }
    //checando as instancias que não terminaram no tempo da simulação:
    for(int i = 0; i < n; i ++){
        if(t[i].estado == 1){
            cont[i].killed ++;  //é dada como killed
        }
    }
}