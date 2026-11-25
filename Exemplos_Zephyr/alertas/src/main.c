#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>
#include <stdlib.h>

#define STACK_SIZE 		1024

#define OFFSET			4
#define QUEUE_SIZE		5
#define MSG_ARRAY_SIZE	10

void tarefa_1(void *arg1, void *arg2, void *arg3);
void tarefa_2(void *arg1, void *arg2, void *arg3);
void tarefa_3(void *arg1, void *arg2, void *arg3);

K_THREAD_STACK_DEFINE(stack_1, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_2, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_3, STACK_SIZE);

K_MSGQ_DEFINE(msg_queue, QUEUE_SIZE, sizeof(int), 2);

struct k_sem s;

int main(void)
{
	struct k_thread tids[3];

	k_sem_init(&s, 0, 1);	

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
	
		k_thread_create(&tids[2], 
					stack_3, 
					STACK_SIZE, 
					tarefa_3, 
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
	const int msg[] = {0, 1};

	while (1) {
		k_msgq_put(&msg_queue, &msg[rand() % 2], K_FOREVER);
		k_msleep(2000);
	}
}

void tarefa_2(void *arg1, void *arg2, void *arg3)
{
	int msg_recebida;

	while (1) {
		k_msgq_get(&msg_queue, &msg_recebida, K_FOREVER);

		switch (msg_recebida) {
			case 1:
				k_sem_give(&s);
				break;
			default:
				printf("Tudo ok\n");
				break;
		}
		k_msleep(2000);
	}
}

void tarefa_3(void *arg1, void *arg2, void *arg3)
{

	while (1) {
		k_sem_take(&s, K_FOREVER);
		printf("<-- O alerta foi acionado -->\n");
		k_msleep(2000);
	}
}