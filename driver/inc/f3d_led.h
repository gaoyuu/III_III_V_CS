/* declarations for f3d_led.c */
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

void f3d_led_init(void);

void f3d_led_off(int led);

void f3d_led_on(int led);

void f3d_led_all_on(void);

void f3d_led_all_off(void);




