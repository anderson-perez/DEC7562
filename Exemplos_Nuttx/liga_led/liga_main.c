#include <stdio.h>
#include <nuttx/config.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <nuttx/ioexpander/gpio.h>

int main(int argc, char** argv)
{
  int pino_15, pino_18, entrada = 0;

  pino_15 = open("/dev/gpio0", O_RDWR);
  pino_18 = open("/dev/gpio1", O_RDWR);

  if (pino_15 <= 0 || pino_18 <= 0) {
    printf("Nao foi possivel abrir o dispositivo\n");
    exit(0);
  }

  /*
  // Para ficar piscando o led
  while (1) {
    ioctl(pino_15, GPIOC_WRITE, 1);
    sleep(2);
    ioctl(pino_15, GPIOC_WRITE, 0);
    sleep(2);
  }
  */

  while (1) {
    ioctl(pino_18, GPIOC_READ, &entrada);
    if (entrada) {
      ioctl(pino_15, GPIOC_WRITE, 1);
    }
    else {
      ioctl(pino_15, GPIOC_WRITE, 0);
    }
    sleep(1);
  }

  close(pino_15);
  close(pino_18);

  return 0;
}