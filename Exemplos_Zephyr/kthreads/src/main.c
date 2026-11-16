#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>

#define STACK_SIZE 1024

void tarefa_1(void *arg1, void *arg2, void *arg3);
void tarefa_2(void *arg1, void *arg2, void *arg3);

K_THREAD_STACK_DEFINE(stack_1, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_2, STACK_SIZE);

int main(void)
{
	struct k_thread tids[2];

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
		printf("Kthread 1 executando ...\n");
	}
}

void tarefa_2(void *arg1, void *arg2, void *arg3)
{
	while (1) {
		printf("Kthread 2 executando ...\n");
	}
}
