
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../local_dev/include/esp01s_pins.h"
#include "../../local_dev/include/local_defs.h"
#include "../../local_dev/include/pin_init.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_http_client.h"


#define TAG "HTTP_CLIENT"
#define HTTP_BUF_FAIL 1
#define HTTP_BUF_SUCC 0
#define HTTP_RECV_BUFSZ (4 * 1024)
static unsigned char http_recv_buffer[HTTP_RECV_BUFSZ];
static unsigned int http_read_ind = 0;
static unsigned int http_write_ind = 0;



// write at most HTTP_RECV_BUFSZ data bytes to ring buffer
// update read ptr if old data is overwritten
int http_buf_write(void* data, int len)
{
    if (len > HTTP_RECV_BUFSZ)
        return HTTP_BUF_FAIL;
    unsigned int write_start = http_write_ind;
    unsigned char* readptr = (unsigned char*)data;
    for (int i = 0; i < len; ++i, ++http_write_ind)
        http_recv_buffer[http_write_ind % HTTP_RECV_BUFSZ] = readptr[i];
    if ((http_write_ind - http_read_ind) >= HTTP_RECV_BUFSZ)
        http_read_ind = write_start;
    return HTTP_BUF_SUCC;
}

// return view of data to caller. volatile, copy if 
// persistent data is needed.
unsigned char* http_buf_read(int max_len, int* read_len)
{
    if (http_read_ind == http_write_ind) {
        *read_len = 0;
        return NULL;
    }
    *read_len = (http_write_ind - http_read_ind) % HTTP_RECV_BUFSZ;
    unsigned char* ret_ptr = http_recv_buffer + *read_len;
    http_read_ind = http_write_ind;
    return ret_ptr;
}

static esp_err_t _http_event_handler(esp_http_client_event_t* evt)
{
    switch (evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, val=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, bytelen: %d", evt->data_len);
            if (http_buf_write(evt->data, evt->data_len) != HTTP_BUF_SUCC) {
                ESP_LOGE(TAG, "failed to write http payload to recv buffer!");
                return ESP_FAIL;
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
    }

    return ESP_OK;
}

void sample_request() {

    ESP_LOGI(TAG, "starting sample request routine...");

    esp_http_client_config_t config = {
        .host = "ifconfig.me",
        .path = "/get",
        .event_handler = _http_event_handler,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err;
    if ((err = esp_http_client_perform(client)) != ESP_OK) {
        const char* err_text = esp_err_to_name(err);
        ESP_LOGE(TAG, "failed to perform http req: %s", err_text);
        return;
    }

    // attempt to read found data
    int read_len = 0;
    unsigned char* read_data = http_buf_read(HTTP_RECV_BUFSZ, &read_len);
    if (!read_data) {
        ESP_LOGE(TAG, "failed to read payload data from buffer");
        return;
    }

    printf("read data of len:%d\n", read_len);
    for (int i = 0; i < read_len; ++i) {
        printf("%c", read_data[i]);
        if (i && i % 32 == 0) printf("\n");
    }
}
