#include <nuttx/config.h>
#include <stdio.h>
#include <pthread.h>
#include <mqueue.h>

void *thread_envia(void *args);
void *thread_recebe(void *args);

// Fila de mensagens
mqd_t mensagem;

int main(int argc, FAR char *argv[])
{
  pthread_t tids[2];

  // Cria a fila de mensagens
  struct mq_attr msg_attr;

  msg_attr.mq_msgsize = sizeof(int);
  msg_attr.mq_maxmsg = 5;
  msg_attr.mq_curmsgs = 0;
  msg_attr.mq_flags = 0;


  mensagem = mq_open("/dados", O_CREAT | O_RDWR | O_NONBLOCK, 0644, &msg_attr);

  pthread_create(&tids[0], NULL, thread_envia, NULL);
  pthread_create(&tids[1], NULL, thread_recebe, NULL);

  pthread_join(tids[0], NULL);

  mq_close (mensagem);
  mq_unlink("/dados");

  return 0;
}

void *thread_envia(void *args)
{
  int dados[] = {1, 2, 3, 4, 5}, i = 0;

  while (1) {
    
    if (!mq_send(mensagem, (const char*)&dados[i], sizeof(int), 0)) {
      printf("Thread enviando %d ...\n", dados[i]);
      i = (i+1) % 5;
    }
    sleep(1);
  }

  return NULL;
}

void *thread_recebe(void *args)
{
  int dado_recebido;

  while (1) {
    mq_receive(mensagem, (char*)&dado_recebido, sizeof(int), 0);
    printf("Thread recebeu %d\n", dado_recebido);
    sleep(10);  
  }

  return NULL;
}

