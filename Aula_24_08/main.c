#include <xc.h>

#define LIGAR_TIMER1() T1CONbits.TON = 1
#define DESLIGAR_TIMER1() T1CONbits.TON = 0

#define FCY 16000000    // 16 MHz

typedef enum {READY = 0, RUNNING, WAITING} t_state;

typedef void (*f_ptr)(void);

typedef struct tcb {
    unsigned int prioridade;
    t_state estado;
    f_ptr tarefa;
} tcb_t;


void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void);

void config_timer1();
void config_ports();

void criar_tarefa(unsigned int prior, f_ptr tarefa, t_state estado);

void led_1();
void led_2();
void led_3();


// Variáveis globais
tcb_t tarefas[3];
int qtd_tasks = 0, task_running = 0;

int main()
{
    config_ports();
    config_timer1();
    
    LIGAR_TIMER1();
    
    while (1) {
        tarefas[task_running].tarefa();
    }
    
    return 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;
    task_running = (task_running+1) % 3;
}

void config_timer1()
{
    T1CONbits.TCS = 0;          // Clock interno 
    T1CONbits.TCKPS = 0b01;     // Preescaler 1:8
    IFS0bits.T1IF = 0;          // Flag
    IEC0bits.T1IE = 1;          // Atividação da interrupção por timer
    IPC0bits.T1IP = 4;          // Prioridade
    PR1 = 1999;
}

void config_ports()
{
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISFbits.TRISF6 = 1;
}

void led_1()
{
    LATEbits.LATE0 ^= 1;
}

void led_2()
{
    LATEbits.LATE1 ^= 1;
}

void led_3()
{
    LATEbits.LATE2 ^= 1;
}

void criar_tarefa(unsigned int prior, f_ptr tarefa, t_state estado)
{
    tarefas[qtd_tasks].estado = estado;
    tarefas[qtd_tasks].prioridade = prior;
    tarefas[qtd_tasks++].tarefa = tarefa;
}
