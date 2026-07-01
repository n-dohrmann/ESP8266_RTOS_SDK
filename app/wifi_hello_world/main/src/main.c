/* WiFi station Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "../../local_dev/include/esp01s_pins.h"
#include "../../local_dev/include/local_defs.h"
#include "../../local_dev/include/pin_init.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <string.h>

#include "lwip/err.h"
#include "lwip/sys.h"
#include "projdefs.h"

// local config
#include "../include/local_secrets.h"
#include "../include/wifi_conn.h"

extern void wifi_init_sta(void);
extern void wifi_close_sta(void);
extern void sample_request(void);

// turn off both pins
void pin_off(void)
{
    gpio_set_level(ESP01S_GPIO0_NUM, GPIO_LOW);
    gpio_set_level(ESP01S_GPIO2_NUM, GPIO_LOW);
}

// turn on both io0 (red led) and io2 (green led) as output pins
esp_err_t pin_init(void)
{
    esp_err_t sc;
    if ((sc = pin_default_out(ESP01S_GPIO2_BIT) != ESP_OK))
        return sc;
    if ((sc = pin_default_out(ESP01S_GPIO0_BIT) != ESP_OK))
        return sc;

    // turn off both pins
    pin_off();
    return ESP_OK;
}

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());

    // ESP_ERROR_CHECK(pin_init());

    for (int tt = 10; tt; --tt) {
        printf("starting wifi connect in %d...\n", tt);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    // attempt to perform http request
    sample_request();

    vTaskDelay(pdMS_TO_TICKS(10000));
    printf("Disconnecting...\n");
    wifi_close_sta();
}
