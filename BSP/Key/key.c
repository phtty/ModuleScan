#include "key.h"
#include "display.h"
#include "function.h"
#include "gpio.h"

bool key_reflash_flag = false;
// KeyStatus key_flag         = key_none;

void handle_key(void)
{
    if (key_reflash_flag == false)
        return;
    key_reflash_flag = false;

    HAL_Delay(5);

    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10)) {
        display_fill(black);

    } else if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)) {
        display_stop_flag();

    } else if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12)) {
        display_high_limit();
    }
}