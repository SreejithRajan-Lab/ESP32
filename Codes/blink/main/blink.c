#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED GPIO_NUM_2   // Change if your board uses a different LED pin

void app_main(void)
{
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(LED, 1);   // LED ON
        vTaskDelay(pdMS_TO_TICKS(1000));

        gpio_set_level(LED, 0);   // LED OFF
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
