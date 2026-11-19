#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


void *thread_1(void *args);
void *thread_2(void *args);

sem_t s_th_1, s_th_2;

int main(void)
{
	pthread_t tids[2];

	sem_init(&s_th_1, 0, 0);
	sem_init(&s_th_2, 0, 1);

	pthread_create(&tids[0], NULL, thread_1, NULL);
	pthread_create(&tids[1], NULL, thread_2, NULL);

	pthread_join(tids[0], NULL);

	return 0;
}

void *thread_1(void *args)
{
	while (1) {
		sem_wait(&s_th_1);
		printf("Thread 1 executando ...\n");
		sleep(3);
		sem_post(&s_th_2);
	}
}

void *thread_2(void *args)
{
	while (1) {
		sem_wait(&s_th_2);
		printf("Thread 2 executando ...\n");
		sleep(2);
		sem_post(&s_th_1);
	}
}
