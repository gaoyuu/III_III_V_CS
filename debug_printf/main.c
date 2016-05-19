/**********************************************************
* main.c
*
*   Author: Kyle Dijkstra with Yu Gao
---
*   Date Created: 2/25/16
---
*   Last Modified by: Kyle Dijkstra
---
*   Date Last Modified: 2/26/16
---
*   Assignment: Lab7
---
*/
/* main.c 
   debug this function using gdb*/


/*
  The expected performace of the program is as follows:
  We want to print out the actual bits of numbers! What a great
  way to understand how number representation works

 */

//The libraries to include
#include <f3d_uart.h>
#include <stdio.h> 
#include <stdint.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers
//The arrays that store the bits
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

//runs some test on our program
int main(){
  f3d_uart_init();
  f3d_led_init();
  f3d_user_btn_init();
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  while(1) {
    f3d_led_on(0);
    printf("Hello World\n");
    printf("Goodbye\n");
    printf("Hello World\n");
    printf("Goodbye\n");
    printf("Hello World\n");
    printf("Goodbye\n");
    printf("Hello World\n");
    printf("Goodbye\n");

    delay();
    delay();
    f3d_led_off(0);
    printf("Hello World\n");
    printf("Goodbye\n");
    printf("Hello World\n");
    printf("Goodbye\n");
    printf("Hello World\n");
    printf("Goodbye\n");
    printf("Hello World\n");
    printf("Goodbye\n");
    delay();
    delay();
    f3d_led_on(0);
    f3d_led_on(1);
    //printf("Hello World\n");
    //printf("Goodbye\n");
    delay();
    delay();
    f3d_led_off(1);
    //    printf("Hello World\n");
    //    printf("Goodbye\n");
    delay();
    delay();
    f3d_led_on(1);
    
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
