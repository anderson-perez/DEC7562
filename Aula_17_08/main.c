#include <xc.h>

void task_1();
void task_2();
void task_3();

void config_ports();

typedef void (*f_ptr)(void);

f_ptr tarefas[] = {task_1, task_2, task_3};
unsigned int idx = 0;

int main()
{
    config_ports();
    
    while (1) {
        if (PORTFbits.RF6) {            
            idx = (idx+1) % 3;
        }        
        tarefas[idx]();
        asm("nop");
    }
    
    return 0;
}

void task_1()
{
    LATEbits.LATE0 = ~PORTEbits.RE0;
}

void task_2()
{
    LATEbits.LATE1 = ~PORTEbits.RE1;    
}

void task_3()
{
    LATEbits.LATE2 = ~PORTEbits.RE2;
}

void config_ports()
{
    // Configura pinos E0, E1 e E2 para 
    // saída de dados.
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISFbits.TRISF6 = 1;
}