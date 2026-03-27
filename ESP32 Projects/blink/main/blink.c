#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_PIN GPIO_NUM_5s
void app_main(void)
{
    gpio_reset_pin(LED_PIN);   // RESET THE PIN TO ELIMINATE GARBAGE 
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT); // SETTING GPIO PIN 2 AS OUTPUT

    while(1)
    {
        gpio_set_level(LED_PIN,1); //LED ON
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay of 1000 ms
        gpio_set_level(LED_PIN,0); //LED OFF
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay of 1000 ms
    }


}
