#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SAIDA   18
#define ENTRADA 19

int main()
{
    const struct device *driver = DEVICE_DT_GET(DT_NODELABEL(gpio0));

    if (!device_is_ready(driver)) {
        printf("Não foi possível abrir gpio0\n");
        return -1;
    }

    gpio_pin_configure(driver, SAIDA, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure(driver, ENTRADA, GPIO_INPUT);

    while (1) {
        int entrada = gpio_pin_get(driver, ENTRADA);

        if (entrada == 1) {
            gpio_pin_set(driver, SAIDA, 1);
        }
        else {
            gpio_pin_set(driver, SAIDA, 0);
        }
    }

    return 0;
}