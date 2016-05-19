/**********************************************************
 * main.c
 *
 * The main function to light up the leds with certian order.
 *
 * Author: Yangjun Liu(liu282), Yu Gao(gaoyu)
 * Date Created: 3/31/2016
 * Last Modified by: Yangjun
 * Date Last Modified: 4/7/2016
 * Assignment: Lab11
 * Part of: CSCI-C335 Spring 2016
 */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_systick.h>

//main function to init the led, user button and the logic of led outputs.
int main(void) {
  f3d_uart_init();
  f3d_led_init();
  f3d_user_btn_init();
  f3d_systick_init();

  while(1) {
    putchar(getchar());
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
