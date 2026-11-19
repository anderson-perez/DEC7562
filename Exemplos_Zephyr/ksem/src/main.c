#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>

#define STACK_SIZE 1024

void tarefa_1(void *arg1, void *arg2, void *arg3);
void tarefa_2(void *arg1, void *arg2, void *arg3);

K_THREAD_STACK_DEFINE(stack_1, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_2, STACK_SIZE);

struct k_sem k_th_s1, k_th_s2;

int main(void)
{
	struct k_thread tids[2];

	// Inicializar os semáforos
	k_sem_init(&k_th_s1, 0, 1);
	k_sem_init(&k_th_s2, 1, 1);

	k_thread_create(&tids[0], 
					stack_1, 
					STACK_SIZE, 
					tarefa_1, 
					NULL,
					NULL,
					NULL,
					8,
					0,
					K_NO_WAIT);

	k_thread_create(&tids[1], 
					stack_2, 
					STACK_SIZE, 
					tarefa_2, 
					NULL,
					NULL,
					NULL,
					8,
					0,
					K_NO_WAIT);

	k_thread_join(&tids[0], K_FOREVER);

	return 0;
}

void tarefa_1(void *arg1, void *arg2, void *arg3)
{
	while (1) {
		k_sem_take(&k_th_s1, K_FOREVER);
		printf("Kthread 1 executando ...\n");
		k_msleep(2000);
		k_sem_give(&k_th_s2);
	}
}

void tarefa_2(void *arg1, void *arg2, void *arg3)
{
	while (1) {
		k_sem_take(&k_th_s2, K_FOREVER);
		printf("Kthread 2 executando ...\n");
		k_msleep(3000);
		k_sem_give(&k_th_s1);
	}
}
