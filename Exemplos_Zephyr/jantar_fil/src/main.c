#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>

#define STACK_SIZE 1024
#define N 5
#define SLEEP_EATING 3000
#define SLEEP_SLEEP 2000

void tarefa_1(void *arg1, void *arg2, void *arg3);
void tarefa_2(void *arg1, void *arg2, void *arg3);
void tarefa_3(void *arg1, void *arg2, void *arg3);
void tarefa_4(void *arg1, void *arg2, void *arg3);
void tarefa_5(void *arg1, void *arg2, void *arg3);

K_THREAD_STACK_DEFINE(stack_1, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_2, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_3, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_4, STACK_SIZE);
K_THREAD_STACK_DEFINE(stack_5, STACK_SIZE);

struct k_sem k_th[N];

int main(void)
{
	struct k_thread tids[N];
	int indexes[N] = {0, 1, 2, 3, 4};

	// Inicializar os semáforos
	for (int i = 0; i < N; i++)
		k_sem_init(&k_th[i], 1, 1);

	k_thread_create(&tids[0],
					stack_1,
					STACK_SIZE,
					tarefa_1,
					&indexes[0],
					NULL,
					NULL,
					8,
					0,
					K_NO_WAIT);

	k_thread_create(&tids[1],
					stack_2,
					STACK_SIZE,
					tarefa_2,
					&indexes[1],
					NULL,
					NULL,
					8,
					0,
					K_NO_WAIT);

	k_thread_create(&tids[2],
					stack_3,
					STACK_SIZE,
					tarefa_3,
					&indexes[2],
					NULL,
					NULL,
					8,
					0,
					K_NO_WAIT);

	k_thread_create(&tids[3],
					stack_4,
					STACK_SIZE,
					tarefa_4,
					&indexes[3],
					NULL,
					NULL,
					8,
					0,
					K_NO_WAIT);

	k_thread_create(&tids[4],
					stack_5,
					STACK_SIZE,
					tarefa_5,
					&indexes[4],
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
	int idx = *(int *)arg1;
	int next = (idx + 1) % N;

	while (1)
	{
		k_sem_take(&k_th[idx], K_FOREVER);
		k_sem_take(&k_th[next], K_FOREVER);
		printf("Filosofo %i esta comendo...\n", idx);
		k_msleep(SLEEP_EATING);
		k_sem_give(&k_th[idx]);
		k_sem_give(&k_th[next]);
		printf("Filosofo %i esta dormindo...\n", idx);
		k_msleep(SLEEP_SLEEP);
	}
}

void tarefa_2(void *arg1, void *arg2, void *arg3)
{
	int idx = *(int *)arg1;
	int next = (idx + 1) % N;

	while (1)
	{
		k_sem_take(&k_th[idx], K_FOREVER);
		k_sem_take(&k_th[next], K_FOREVER);
		printf("Filosofo %i esta comendo...\n", idx);
		k_msleep(SLEEP_EATING);
		k_sem_give(&k_th[idx]);
		k_sem_give(&k_th[next]);
		printf("Filosofo %i esta dormindo...\n", idx);
		k_msleep(SLEEP_SLEEP);
	}
}

void tarefa_3(void *arg1, void *arg2, void *arg3)
{
	int idx = *(int *)arg1;
	int next = (idx + 1) % N;

	while (1)
	{
		k_sem_take(&k_th[idx], K_FOREVER);
		k_sem_take(&k_th[next], K_FOREVER);
		printf("Filosofo %i esta comendo...\n", idx);
		k_msleep(SLEEP_EATING);
		k_sem_give(&k_th[idx]);
		k_sem_give(&k_th[next]);
		printf("Filosofo %i esta dormindo...\n", idx);
		k_msleep(SLEEP_SLEEP);
	}
}

void tarefa_4(void *arg1, void *arg2, void *arg3)
{
	int idx = *(int *)arg1;
	int next = (idx + 1) % N;

	while (1)
	{
		k_sem_take(&k_th[idx], K_FOREVER);
		k_sem_take(&k_th[next], K_FOREVER);
		printf("Filosofo %i esta comendo...\n", idx);
		k_msleep(SLEEP_EATING);
		k_sem_give(&k_th[idx]);
		k_sem_give(&k_th[next]);
		printf("Filosofo %i esta dormindo...\n", idx);
		k_msleep(SLEEP_SLEEP);
	}
}

void tarefa_5(void *arg1, void *arg2, void *arg3)
{
	int idx = *(int *)arg1;
	int next = (idx + 1) % N;

	while (1)
	{
		k_sem_take(&k_th[next], K_FOREVER);
		k_sem_take(&k_th[idx], K_FOREVER);
		printf("Filosofo %i esta comendo...\n", idx);
		k_msleep(SLEEP_EATING);
		k_sem_give(&k_th[idx]);
		k_sem_give(&k_th[next]);
		printf("Filosofo %i esta dormindo...\n", idx);
		k_msleep(SLEEP_SLEEP);
	}
}