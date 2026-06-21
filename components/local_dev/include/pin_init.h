
#include "driver/gpio.h"
#include "esp_err.h"

// set pin number as ouput, no interrupts or pull up/down
esp_err_t pin_default_out(uint32_t pin_bit_mask);
