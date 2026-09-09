#include "escalonador.h"
#include <string.h>

void simulacao(Tarefa * t, Contagem * cont, int n, int tempo_total, char * algoritmo, char rodou[][100], char * situacao){
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
            strcpy(rodou[tempo], t[escolhida].nome);
            t[escolhida].burst_restante --;
            if(t[escolhida].burst_restante == 0){   //se acabou o burst, a instancia foi concluída
                t[escolhida].estado = 0;
                cont[escolhida].complete ++;    //fica em espera e é dada como complete
                situacao[tempo] = 'F';
            }
            else{
                situacao[tempo] = 'H';
            }
        } else{
            strcpy(rodou[tempo], "idle");
            situacao[tempo] = ' ';
        }

        //verificando se chegou no deadline e o prazo acabou
        for(int i = 0; i < n; i ++){
            if (t[i].estado == 1){
                t[i].deadline_restante --;
                if(t[i].deadline_restante == 0){    //se a tarefa não concluiu dentro do prazo:
                    t[i].estado = 2;    
                    cont[i].lost ++;    //o processo encerra e é dado como lost
                    if(i == escolhida){
                        situacao[tempo] = 'L';   
                    }
                }
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

void gerarLog(char rodou[][100], int tempo_total, FILE * output, char * situacao){
    int i = 0;
    while(i < tempo_total){
        int duracao = 1;
        while((i + duracao) < tempo_total && strcmp(rodou[i + duracao], rodou[i]) == 0 && situacao[i + duracao - 1] != 'L' && situacao[i + duracao - 1] != 'F'){
            duracao ++;
        }

        int ultimo = i + duracao - 1;

        if (strcmp(rodou[i], "idle") == 0){
            fprintf(output, "idle for %d units\n",duracao);
        } else{
            fprintf(output, "[%s] for %d units - %c\n", rodou[i], duracao, situacao[ultimo]);
        }
        i += duracao;
    }
}

void escreverResumo(Tarefa *t, Contagem *cont, int n, FILE *output) {
    fprintf(output, "\nLOST DEADLINES\n");
    for (int i = 0; i < n; i++) {
        fprintf(output, "[%s] %d\n", t[i].nome, cont[i].lost);
    }

    fprintf(output, "\nCOMPLETE EXECUTION\n");
    for (int i = 0; i < n; i++) {
        fprintf(output, "[%s] %d\n", t[i].nome, cont[i].complete);
    }

    fprintf(output, "\nKILLED\n");
    for (int i = 0; i < n; i++) {
        fprintf(output, "[%s] %d\n", t[i].nome, cont[i].killed);
    }
}