
// blink example...

#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../../components/local_dev/include/local_defs.h"
#include "driver/gpio.h"


#ifndef GPIO_HIGH
#define GPIO_HIGH 1
#endif // GPIO_HIGH

#ifndef GPIO_LOW
#define GPIO_LOW 0
#endif // GPIO_LOW


// built-in LED pin connected to gpio pin 2
#define LED_BUILTIN GPIO_NUM_2
#define SECONDS(x) (((TickType_t)x * 1000) / portTICK_PERIOD_MS)

// gpio and other init tasks
esp_err_t init()
{
    esp_err_t sc = ESP_OK;

    // configure gpio 2 (LED_BUILTIN) to be an output pin
    gpio_config_t config;
    config.pin_bit_mask = GPIO_Pin_2;
    config.mode = GPIO_MODE_OUTPUT;
    config.intr_type = GPIO_INTR_DISABLE;
    config.pull_down_en = 0;
    config.pull_up_en = 0;
    if ((sc = gpio_config(&config)) != ESP_OK)
        return sc;

    return ESP_OK;
}

void toggle()
{
    uint32_t new_level = GPIO_HIGH ^ gpio_get_level(LED_BUILTIN);
    gpio_set_level(LED_BUILTIN, new_level);
    vTaskDelay(SECONDS(1));
}

void app_main()
{
    if (init() != ESP_OK)
        exit(1);

    while (1) {
        toggle();
    }
}
