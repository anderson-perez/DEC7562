/****************************************************************************
 * apps/examples/hello/hello_main.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * hello_main
 ****************************************************************************/

void *thread(void *args);

sem_t s;

int main(int argc, FAR char *argv[])
{
  pthread_t tid;

  if (argc < 3) {
    printf("Erro.\n");
    printf("Uso: %s string vezes\n", argv[0]);
    return -1;
  }

  int vezes = atoi(argv[2]);

  sem_init(&s, 0, 7);

  for (int i = 0; i < vezes; i++) {
    printf("UFSC --> %s\n", argv[1]);
  }

  pthread_create(&tid, NULL, thread, NULL);

  pthread_join(tid, NULL);

  return 0;
}

void *thread(void *args)
{
  for (int i = 0; i < 100; i++) {
    printf("Sou a thread %d executando %i vezes\n", pthread_self(), i+1);    
    sem_wait(&s);
  }

  return NULL;
}