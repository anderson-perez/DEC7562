/**
 * Exemplo para ilustrar a troca de contexto e os escalonadores
 * round-robin e prioridade.
 */

#include "FreeRTOS.h"
#include "task.h"

// Definição das tarefas
void tarefa_1();
void tarefa_2();
void tarefa_3();

void config_tasks();


int main()
{
    config_tasks();
    
    xTaskCreate(tarefa_1, "T1", 128, NULL, 3, NULL);
    xTaskCreate(tarefa_2, "T2", 128, NULL, 3, NULL);
    xTaskCreate(tarefa_3, "T3", 128, NULL, 3, NULL);
    
    vTaskStartScheduler();
    
    while (1);
    
    return 0;
}

// Implementação das tarefas
void tarefa_1()
{
    while (1) {
        LATCbits.LATC1 = ~PORTCbits.RC1;
    }
}

void tarefa_2()
{
    while (1) {
        LATCbits.LATC2 = ~PORTCbits.RC2;
    }
}

void tarefa_3()
{
    while (1) {
        LATCbits.LATC3 = ~PORTCbits.RC3;
    }
}

void config_tasks()
{
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;   
}
