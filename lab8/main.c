/* main.c ---
 *
 * Filename: main.c
 * Description:lab8 compass and tilt
 * Author:gaoyu and ajmjyash
 * Created: 3/3/2016
 * Date Last Modified: 3/6/2016
 /* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000



int main(void) {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // Set up your inits before you go ahead
  f3d_uart_init();
  f3d_user_btn_init();
  f3d_lcd_init();
  f3d_lcd_fillScreen(WHITE);
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);

  float accel_data[3];
  float mag_data[3];
  double accel_pitch, accel_pitch_deg;
  double accel_roll, accel_roll_deg;
  double mag_heading, mag_heading_deg;
  int button = 0;
   
  while(1) {
                    
    if (user_btn_read() == 1 && button == 1) 
      { 
	button = 0; 
	f3d_lcd_fillScreen(WHITE);
      }
    else if (user_btn_read() == 1 && button == 0) 
      { 
	f3d_lcd_fillScreen(WHITE);
	button = 1; 
      }

    if (button == 0) {       
      char pitch[20], roll[20];
      f3d_accel_read(accel_data);

      accel_pitch = atan2( accel_data[0], sqrt(pow(accel_data[1], 2) + pow(accel_data[2], 2)));
      accel_pitch_deg = (180/M_PI) * accel_pitch;
      accel_roll = atan2( accel_data[1], sqrt(pow(accel_data[0], 2) + pow(accel_data[2], 2)));
      accel_roll_deg = (180/M_PI) * accel_roll;
       
      snprintf(pitch, 20, "Pitch: %f", accel_pitch_deg);
      snprintf(roll, 20, "Roll: %f", accel_roll_deg);
     
      f3d_lcd_drawString(0, 40, pitch, BLACK, WHITE);
      f3d_lcd_drawString(0, 50, roll, BLACK, WHITE);

      int X,Y,oldX,oldY;
      X=50+accel_roll_deg;
      Y=100+accel_pitch_deg;
      f3d_lcd_drawString(oldX,oldY,"O",WHITE,WHITE);
      f3d_lcd_drawString(50,100, "o", BLACK, WHITE);
      f3d_lcd_drawString(X,Y,"O",BLACK,WHITE);
      oldX=X,oldY=Y;
       
    }
    else {
      char heading[20];
      f3d_mag_read(mag_data);

      mag_heading = atan2(mag_data[1], mag_data[0]);
      mag_heading_deg = (180/M_PI) * mag_heading;

      //calibrate compass heading
      mag_heading_deg -= 160; 
      if (mag_heading_deg < 0) {
	mag_heading_deg = -mag_heading_deg;
	mag_heading_deg = 360 - mag_heading_deg;
      }

      snprintf(heading, 20, "Heading: %f\n", mag_heading_deg);       
      f3d_lcd_drawString(0, 20, heading, BLACK, WHITE);
	
      int X,Y,oldX,oldY;
      X=50+200*mag_data[1];
      Y=100+200*mag_data[0];
      f3d_lcd_drawString(oldX,oldY,"N",WHITE,WHITE);
      f3d_lcd_drawString(50,100, "o", BLACK, WHITE);
      f3d_lcd_drawString(X,Y,"N",BLACK,WHITE);
      oldX=X,oldY=Y;
    }

  }



  //while(1);
}



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
