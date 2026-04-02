#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"

// WiFi credentials
#define WIFI_SSID "Rajan"
#define WIFI_PASS "9995980519"


// ================= EVENT HANDLER =================
static void wifi_event_handler(void* arg,
                              esp_event_base_t event_base,
                              int32_t event_id,
                              void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        printf("WiFi Started\n");
        esp_wifi_connect();
    }
  else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
{
    wifi_event_sta_disconnected_t* event = (wifi_event_sta_disconnected_t*) event_data;

    printf("Disconnected, reason: %d\n", event->reason);

    esp_wifi_connect();
}
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;

        printf("Connected!\n");
        printf("Got IP: " IPSTR "\n", IP2STR(&event->ip_info.ip));
    }
}


// ================= MAIN =================
void app_main(void)
{
    // 1. Initialize memory
    nvs_flash_init();

    // 2. Initialize network stack
    esp_netif_init();

    // 3. Create event loop
    esp_event_loop_create_default();

    // 4. Create WiFi station
    esp_netif_create_default_wifi_sta();

    // 5. Initialize WiFi driver
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    // 6. Register event handler
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);

    // 7. Configure WiFi
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };

    // 8. Set mode
    esp_wifi_set_mode(WIFI_MODE_STA);

    // 9. Apply config
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);

    // 10. Start WiFi
    esp_wifi_start();

    // Loop
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}