#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "rom/gpio.h"

#define BTN_NUM 14
#define STUDENT_ID 2014567

int btn_cnt = 0;

void btn_check(void *pvParameter)
{
    gpio_pad_select_gpio(BTN_NUM);
    gpio_set_direction(BTN_NUM, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_NUM, GPIO_PULLUP_ONLY);
    while (1) //
    {
        if (gpio_get_level(BTN_NUM) == 0)
            btn_cnt++;
        else
            btn_cnt = 0;

        if (btn_cnt >= 2)
            printf("ESP32\n");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreate(&btn_check, "buttons", 8000, NULL, 1, NULL);
    while (1)
    {
        printf("%d\n", STUDENT_ID);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}