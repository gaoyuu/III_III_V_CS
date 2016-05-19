/**********************************************************
 * main.c
 * sequetial led
 *
 * Author: gaoyu and Erik Bailey eribaile
 * Date Created: 2016/2/4
 * Last Modified by: gaoyu and Erik Bailey eribaile
 * Date Last Modified: 2016/2/6
 * Assignment: lab4
 * Part of: llab4
 *///

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
 
  f3d_led_init();
  f3d_user_btn_init();
  
  int i;

  f3d_led_all_off();
  while(1){
   
   for (i = 0; i <= 7; i++){
      while (user_btn_read()){
	f3d_led_on(i);
      }
      f3d_led_on(i);
      delay();
      f3d_led_off(i);
   }
   f3d_led_all_on();
   delay();
   f3d_led_all_off();	
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

