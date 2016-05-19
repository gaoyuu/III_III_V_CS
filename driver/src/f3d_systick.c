/* f3d_systick.c --- 
 * 
 * Filename: f3d_systick.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Nov 14 07:57:37 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

#include <f3d_systick.h>
#include <f3d_led.h> 
#include <f3d_user_btn.h>
#include <f3d_uart.h>
#include "queue.h"

extern queue_t rxbuf, txbuf;
volatile int systick_flag = 0;
int i = -1;
void f3d_systick_init(void) {
  SysTick_Config(SystemCoreClock/100);
}

void SysTick_Handler(void) {
  //flush uart if queue is empty
  if (!queue_empty(&txbuf)) {
    flush_uart();
  }
  //slow motion when user btn pressed
  if (user_btn_read()) {
    SysTick_Config(SystemCoreClock/10);
  }
  else {
    SysTick_Config(SystemCoreClock/100);
  }
  
  if (i == 8) {
    i = -1;
  }
  //light up led one by one
  else {
    f3d_led_off(i);
    i++;
    f3d_led_on(i);
  }

}
