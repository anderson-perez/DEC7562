#include <stdio.h>
#include <pthread.h>

void *thread_1(void *args);
void *thread_2(void *args);


int main(void)
{
	pthread_t tids[2];

	pthread_create(&tids[0], NULL, thread_1, NULL);
	pthread_create(&tids[1], NULL, thread_2, NULL);

	pthread_join(tids[0], NULL);

	return 0;
}

void *thread_1(void *args)
{
	while (1) {
		printf("Thread 1 executando ...\n");
	}
}

void *thread_2(void *args)
{
	while (1) {
		printf("Thread 2 executando ...\n");
	}
}
