
#include "./include/pin_init.h"

// set pin number as ouput, no interrupts or pull up/down
esp_err_t pin_default_out(uint32_t pin_bit_mask)
{
    gpio_config_t config;
    config.pin_bit_mask = pin_bit_mask;
    config.mode = GPIO_MODE_OUTPUT;
    config.intr_type = GPIO_INTR_DISABLE;
    config.pull_down_en = 0;
    config.pull_up_en = 0;
    return gpio_config(&config);
}
