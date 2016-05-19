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

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

int main(void) { 
  //init all used peripherals, set screen to white
  f3d_lcd_init();
  f3d_lcd_fillScreen(WHITE); 
  f3d_gyro_init();
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  
  //array for getting gyro data
  float val[3];

  while (1){
    //place gyro data into array
    f3d_gyro_getdata(val);
    
    //Strings for text values printed on lcd
    char xaxis[20];
    sprintf(xaxis, "X-Axis: %f", val[0]);
    char yaxis[20];
    sprintf(yaxis, "Y-Axis: %f", val[1]);
    char zaxis[20];
    sprintf(zaxis, "Z-Axis: %f", val[2]);
    
    
    //draw string for x-axis
    f3d_lcd_drawString(10, 20, xaxis, BLACK, WHITE);
    //clear any previous rectangle with white rectangle
    f3d_lcd_drawRectangle(WHITE, 10, 35, 125, 45);
    //based on x-axis value, create a green rectangle for a positive value
    //and a red rectangle for negative values
     if(val[0] > 300){
      f3d_lcd_drawRectangle(GREEN, 10, 35, 125, 45);
    } else if (val[0] > 200) {
      f3d_lcd_drawRectangle(GREEN, 10, 35, 100, 45);
    } else if (val[0] > 100) {
      f3d_lcd_drawRectangle(GREEN, 10, 35, 75, 45);
    } else if (val[0] > 5) {
      f3d_lcd_drawRectangle(GREEN, 10, 35, 50, 45);
    } else if (val[0] < -300) {
      f3d_lcd_drawRectangle(RED, 10, 35, 125, 45);
    }  else if (val[0] < -200) {
      f3d_lcd_drawRectangle(RED, 10, 35, 100, 45);
    } else if (val[0] < -100) {
      f3d_lcd_drawRectangle(RED, 10, 35, 75, 45);
    }  else if (val[0] < -5) {
      f3d_lcd_drawRectangle(RED, 10, 35, 50, 45);
     }

     //same process as the x-axis for y-axis
     f3d_lcd_drawString(10, 50, yaxis, BLACK, WHITE);
     f3d_lcd_drawRectangle(WHITE, 10, 65, 125, 75);
     if(val[1] > 300){
      f3d_lcd_drawRectangle(GREEN, 10, 65, 125, 75);
    } else if (val[1] > 200) {
      f3d_lcd_drawRectangle(GREEN, 10, 65, 100, 75);
    } else if (val[1] > 100) {
      f3d_lcd_drawRectangle(GREEN, 10, 65, 75, 75);
    } else if (val[1] > 5) {
      f3d_lcd_drawRectangle(GREEN, 10, 65, 50, 75);
    } else if (val[1] < -300) {
      f3d_lcd_drawRectangle(RED, 10, 65, 125, 75);
    }  else if (val[1] < -200) {
      f3d_lcd_drawRectangle(RED, 10, 65, 100, 75);
    } else if (val[1] < -100) {
      f3d_lcd_drawRectangle(RED, 10, 65, 75, 75);
    }  else if (val[1] < -5) {
      f3d_lcd_drawRectangle(RED, 10, 65, 50, 75);
     }
    
     //same process as x and y-axis for z-axis
     f3d_lcd_drawString(10, 80, zaxis, BLACK, WHITE);
     f3d_lcd_drawRectangle(WHITE, 10, 95, 125, 105);
     if(val[2] > 300){
      f3d_lcd_drawRectangle(GREEN, 10, 95, 125, 105);
    } else if (val[2] > 200) {
      f3d_lcd_drawRectangle(GREEN, 10, 95, 100, 105);
    } else if (val[2] > 100) {
      f3d_lcd_drawRectangle(GREEN, 10, 95, 75, 105);
    } else if (val[2] > 5) {
      f3d_lcd_drawRectangle(GREEN, 10, 95, 50, 105);
    } else if (val[2] < -300) {
      f3d_lcd_drawRectangle(RED, 10, 95, 125, 105);
    }  else if (val[2] < -200) {
      f3d_lcd_drawRectangle(RED, 10, 95, 100, 105);
    } else if (val[2] < -100) {
      f3d_lcd_drawRectangle(RED, 10, 95, 75, 105);
    }  else if (val[2] < -5) {
      f3d_lcd_drawRectangle(RED, 10, 95, 50, 105);
     }
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
