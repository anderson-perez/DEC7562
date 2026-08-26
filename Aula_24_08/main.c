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

void bubble_sort();
int prior_scheduler();
int rr_scheduler();

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
    
    criar_tarefa(5, led_1, READY);
    criar_tarefa(6, led_2, READY);
    criar_tarefa(3, led_3, READY);
    
    LIGAR_TIMER1();
    
    while (1) {
        if (task_running < 0) continue;
        
        tarefas[task_running].tarefa();
    }
    
    return 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;
    //task_running = (task_running+1) % qtd_tasks;
    task_running = prior_scheduler();
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

inline void bubble_sort()
{
    for (int i = 0; i < qtd_tasks; i++) {
        for (int j = i + 1; j < qtd_tasks; j++) {
            if (tarefas[j].prioridade > tarefas[i].prioridade) {
                tcb_t t = tarefas[j];
                tarefas[j] = tarefas[i];
                tarefas[i] = t;
            }
        }
    }
}

int prior_scheduler()
{
    return 0;
    
    bubble_sort();
    for (int i = 0; i < qtd_tasks; i++) {
        if (tarefas[i].estado == READY) return i;
    }
    
    return -1;
}

int rr_scheduler()
{
    
}
