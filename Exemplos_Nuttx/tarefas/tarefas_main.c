#include <nuttx/config.h>
#include <stdio.h>
#include <pthread.h>
#include <nuttx/sched.h>

#define ON  1
#define OFF 0

#define EXEMPLO_THREADS   OFF
#define EXEMPLO_TAREFAS   ON

#if EXEMPLO_THREADS == ON
void *thread_a(void *args);
void *thread_b(void *args);
#endif

#if EXEMPLO_TAREFAS == ON
int tarefa_1(int argc, char **argv);
int tarefa_2(int argc, char **argv);
#endif

int main(int argc, FAR char *argv[])
{
  #if EXEMPLO_THREADS == ON
  pthread_t tids[2];

  printf("Thread principal criando threads secundárias...\n");

  pthread_create(&tids[0], NULL, thread_a, NULL);
  pthread_create(&tids[1], NULL, thread_b, NULL);

  pthread_join(tids[0], NULL);
  #endif

  #if EXEMPLO_TAREFAS == ON
  task_create("T1", 100, 1024, tarefa_1, NULL);
  task_create("T2", 100, 1024, tarefa_2, NULL);

  #endif

  return 0;
}

#if EXEMPLO_THREADS == ON
void *thread_a(void *args)
{
  while (1) {
    printf("Eu sou a thread A (id: %d)\n", pthread_self());
    sleep(1);
  }
}

void *thread_b(void *args)
{
  while (1) {
    printf("Eu sou a thread B (id: %d)\n", pthread_self());
    sleep(1);
  }
}
#endif

#if EXEMPLO_TAREFAS == ON
int tarefa_1(int argc, char **argv)
{
  while (1) {
    printf("Eu sou a TAREFA 1\n");
    sleep(1);
  }

}

int tarefa_2(int argc, char **argv)
{
  while (1) {
    printf("Eu sou a TAREFA 2\n");
    sleep(1);
  }

}
#endif

