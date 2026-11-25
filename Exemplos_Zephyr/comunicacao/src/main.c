#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>

#define STACK_SIZE 		1024

#define OFFSET			4
#define QUEUE_SIZE		5
#define MSG_ARRAY_SIZE	10

void tarefa_1(void *arg1, void *arg2, void *arg3);
void tarefa_2(void *arg1, void *arg2, void *arg3);

K_THREAD_STACK_DEFINE(stack_1, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_2, STACK_SIZE);

K_MSGQ_DEFINE(f_mensagem, QUEUE_SIZE, sizeof(int), OFFSET);

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
	int mensagens[MSG_ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, idx = 0;

	while (1) {
		printf("Kthread 1 executando ...\n");
		printf("Enviando msg %i para a thread 2...\n", mensagens[idx]);
		k_msgq_put(&f_mensagem, &mensagens[idx], K_FOREVER);
		idx = (idx+1) % MSG_ARRAY_SIZE;
		k_msleep(1000);
	}
}

void tarefa_2(void *arg1, void *arg2, void *arg3)
{
	int msg_recebida;

	while (1) {
		printf("Kthread 2 executando ...\n");
		k_msgq_get(&f_mensagem, &msg_recebida, K_FOREVER);
		printf("Thread 2 recebeu a mensagem %i\n", msg_recebida);
		k_msleep(1000);
	}
}
