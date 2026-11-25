#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/adc.h>

#define ADC_NODE DT_PATH(zephyr_user)

static const struct adc_dt_spec adc_ldr = ADC_DT_SPEC_GET_BY_IDX(ADC_NODE, 0);

int main()
{
    int16_t buffer;

    struct adc_sequence seq = {.buffer = &buffer,
                               .buffer_size = sizeof(buffer)};

    if (!adc_is_ready_dt(&adc_ldr)) return 0;
    
    adc_channel_setup_dt(&adc_ldr);

    while (1) {
        adc_sequence_init_dt(&adc_ldr, &seq);
        adc_read_dt(&adc_ldr, &seq);
        printf("Valor lido...: %d\n", buffer);
        k_msleep(300);
    }

    return 0;
}