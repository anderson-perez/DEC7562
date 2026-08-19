#include <xc.h>

void __attribute__ ((__interrupt__, no_auto_psv)) _INT0Interrupt(void);
void config_int0();
void config_ports();

void led_1();
void led_2();
void led_3();

typedef void (*f_ptr)(void);

f_ptr tarefas[] = {led_1, led_2, led_3};
volatile int task_running = 2;

int main()
{
    config_ports();
    config_int0();
    
    while (1);
    
    return 0;
}

void __attribute__ ((__interrupt__, no_auto_psv)) _INT0Interrupt(void)
{
    IFS0bits.INT0IF = 0;
    task_running = (task_running+1) % 3;
    tarefas[task_running]();
}

void config_int0()
{
    // Configuração da interrupção externa zero.
    // Polaridade positiva
    INTCON2bits.INT0EP = 0;
    // Flag da interrupção
    IFS0bits.INT0IF = 0;
    // Habilita a interrupção
    IEC0bits.INT0IE = 1;
    // Prioridade
    IPC0bits.INT0IP = 4;
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
