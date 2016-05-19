
/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Yu Gao(gaoyu) with omawhite
 * Maintainer: 
 * Created: March. 24 2016
 * Last-Updated: Mar. 31 2016
 *           By: Yu Gao
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */


#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "bmp.h"
struct bmpfile_magic magic; 
struct bmpfile_header header; 
BITMAPINFOHEADER info;
struct bmppixel pix[128];


void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
BYTE Buff[128];		/* File read buffer */
char filename[20] = "1.bmp";
/*our helper functions */

void drawpicture();
void drawnextpicture();
void drawprevpicture();

//values for calculation
float pitch, roll, pitchN, rollN, magy2, magx2, heading;

int picture = 0;
float accel_data[3];
float mag_data[3];
double accel_pitch, accel_pitch_deg;
double accel_roll, accel_roll_deg;
double mag_heading, mag_heading_deg;
float val[3];



int main(void) { 

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);



  f3d_uart_init();
  f3d_gyro_init();
  f3d_lcd_init();
  f3d_led_init();
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(50);
  f3d_mag_init();
  f3d_nunchuk_init();
  delay(50);

 
  


  //for switching between our files
  //filename = "1.bmp";
  f3d_lcd_fillScreen(BLACK);
  drawpicture();
nunchuk_t nun; 
  while (1) {
    f3d_accel_read(accel_data);
   
    accel_pitch = atan2( accel_data[0], sqrt(pow(accel_data[1], 2) + pow(accel_data[2], 2)));
    accel_roll = atan2( accel_data[1], sqrt(pow(accel_data[0], 2) + pow(accel_data[2], 2)));

    accel_pitch_deg = (180/M_PI) * accel_pitch;
    accel_roll_deg = (180/M_PI) * accel_roll;
    
    f3d_nunchuk_read(&nun);
    if (nun.c == 1) {picture++; drawnextpicture();}
    f3d_nunchuk_read(&nun);
    if (nun.z == 1) {picture--; drawprevpicture();}

     printf("%d, %d\n", nun.c, nun.z);

     f3d_accel_read(accel_data);
     
     
  }
}






  
  //***************************
  //lab work here

void drawpicture(){
  printf("picture value: %d\n", picture);
  //f3d_lcd_fillScreen(RED);
  char footer[20];
  int count=0;
  int i;

  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;
  f_mount(0, &Fatfs);
  
  //f3d_lcd_fillScreen(BLUE);

  rc = f_open(&Fil, filename, FA_READ);
  if (rc) die(rc);
  

  rc = f_read(&Fil, &magic, sizeof(magic ), &br);
  //  printf("Magic %c%c\n", magic.magic[0], magic.magic[1]); 
  rc = f_read(&Fil, &header, sizeof(header), &br);
  //printf("file size %d offset %d\n", header.filesz, header.bmp_offset);
  rc = f_read(&Fil, &info, sizeof(info), &br);
  //printf("Width %d Height %d, bitspp %d\n", info.width, info.height, info.bitspp);
 
  //we dont get to heref3d_lcd_fillScreen(BLUE);
  uint16_t color;
  uint16_t colors[ST7735_width];
  int row,col;

  for(row = 0; row < 160; row++){

    rc = f_read(&Fil, &pix, sizeof pix, &br);
    if(rc) die(rc);
    
    for (i =0; i < 128; i++) {
      color = ((pix[i].r >> 3) << 11) | ((pix[i].g >> 2) << 5) | (pix[i].b >>3);
      colors[i] = color;
    }
    f3d_lcd_setAddrWindow(0,159-row,ST7735_width-1,159-row,MADCTLGRAPHICS);
    f3d_lcd_pushColor(colors, 128); 
  }

  printf("\nClose the file.\n");
  rc = f_close(&Fil);

  //***************************
}

void drawprevpicture(){
  picture = picture % 3;
  if (picture ==-1) {
    picture = 2;}
  if (picture ==0) {
    strcpy(filename,"1.bmp");
    drawpicture();
  }
  else  if (picture ==1) {
    strcpy(filename,"2.bmp");
    drawpicture();
  }
  else if (picture ==2) {
    strcpy(filename,"3.bmp");
    drawpicture();
  }
}

void drawnextpicture(){
  picture = picture % 3;
  if (picture ==0) {
    strcpy(filename,"1.bmp");
    drawpicture();
  }
  else if (picture ==1) {
    strcpy(filename,"2.bmp");
    drawpicture();
  }
  else if (picture ==2) {
    strcpy(filename,"3.bmp");
    drawpicture();
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



