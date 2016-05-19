
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
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_timer2.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <f3d_dac.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>


#define TIMER 20000
#define AUDIOBUFSIZE 128

extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

FATFS Fatfs;		/* File system object */
FIL fid;		/* File object */
BYTE Buff[512];		/* File read buffer */
int ret;

void play(void); /*function that play the wav file */

struct ckhd {
  uint32_t ckID;
  uint32_t cksize;
};

struct fmtck {
  uint16_t wFormatTag;      
  uint16_t nChannels;
  uint32_t nSamplesPerSec;
  uint32_t nAvgBytesPerSec;
  uint16_t nBlockAlign;
  uint16_t wBitsPerSample;
};

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID) {
  f_read(fid, hd, sizeof(struct ckhd), &ret);
  if (ret != sizeof(struct ckhd))
    exit(-1);
  if (ckID && (ckID != hd->ckID))
    exit(-1);
}

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

char fileName[30];

int main(void) { 

  int step = 0;
  int stepMod;
  nunchuk_t n;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_i2c1_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_rtc_init();
  //printf("check rtc\n");
  delay(10);

  f3d_uart_init();
  f3d_timer2_init();
  //printf("check timer2\n");
  f3d_dac_init();
  //printf("check dac\n");
  f3d_delay_init();
  //printf("check delay\n");
  f3d_led_init();
  //printf("check led\n");
  f3d_lcd_init();
  //printf("check lcd\n");
  f3d_systick_init();
  //printf("check systick\n");
  f3d_user_btn_init();
  //printf("check user btn\n");

  f3d_lcd_fillScreen(WHITE);
  
  while (1){
    f3d_nunchuk_read(&n);
    if(n.jy > 150){
      step++;
    }
    if(n.jy < 15){
      step--;
    }
    
    stepMod = abs(step)%3;
    switch(stepMod) {
    case 0:
      strcpy(fileName, "thermo.wav");
      f3d_lcd_drawString(20,10,"Thermo",RED,BLACK);
      f3d_lcd_drawString(20,30,"Lion",RED,WHITE);
      f3d_lcd_drawString(20,50,"Batman",RED,WHITE);
      if(user_btn_read() == 1){
        play();
      }
      break;
    case 1:
      strcpy(fileName, "lion.wav");
      f3d_lcd_drawString(20,10,"Thermo",RED,WHITE);
      f3d_lcd_drawString(20,30,"Lion",RED,BLACK);
      f3d_lcd_drawString(20,50,"Batman",RED,WHITE);
      if(user_btn_read() == 1){
        play();
      }
      break;
    case 2:
      strcpy(fileName, "batman.wav");
      f3d_lcd_drawString(20,10,"Thermo",RED,WHITE);
      f3d_lcd_drawString(20,30,"Lion",RED,WHITE);
      f3d_lcd_drawString(20,50,"Batman",RED,BLACK);
      if(user_btn_read() == 1){
        play();
      }
      break;
    }
  }
}

void play(){

  FRESULT rc;
  DIR dir;
  FILINFO fno;
  UINT bw, br;
  unsigned int retval;
  int bytesread;

  f_mount(0, &Fatfs);/* Register volume work area */

  rc = f_open(&fid, fileName, FA_READ);
  
  if (!rc) {
    struct ckhd hd;
    uint32_t  waveid;
    struct fmtck fck;
    
    readckhd(&fid, &hd, 'FFIR');
    
    f_read(&fid, &waveid, sizeof(waveid), &ret);
    if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
      return ;//-1
    
    readckhd(&fid, &hd, ' tmf');
    
    f_read(&fid, &fck, sizeof(fck), &ret);
    
    // skip over extra info
    
    if (hd.cksize != 16) {
      printf("extra header info %d\n", hd.cksize - 16);
      f_lseek(&fid, hd.cksize - 16);
    }
    
    printf("audio format 0x%x\n", fck.wFormatTag);
    printf("channels %d\n", fck.nChannels);
    printf("sample rate %d\n", fck.nSamplesPerSec);
    printf("data rate %d\n", fck.nAvgBytesPerSec);
    printf("block alignment %d\n", fck.nBlockAlign);
    printf("bits per sample %d\n", fck.wBitsPerSample);
    
    // now skip all non-data chunks !
    
    while(1){
      readckhd(&fid, &hd, 0);
      if (hd.ckID == 'atad')
	break;
      f_lseek(&fid, hd.cksize);
    }
    
    printf("Samples %d\n", hd.cksize);
    
    // Play it !
    
    //      audioplayerInit(fck.nSamplesPerSec);
    
    f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
    hd.cksize -= ret;
    printf("playing sound %s\n", fileName);
    audioplayerStart();
    while (hd.cksize) {
      int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
      if (audioplayerHalf) {
	if (next < AUDIOBUFSIZE/2)
	  bzero(Audiobuf, AUDIOBUFSIZE/2);
	f_read(&fid, Audiobuf, next, &ret);
	hd.cksize -= ret;
	audioplayerHalf = 0;
      }
      if (audioplayerWhole) {
	if (next < AUDIOBUFSIZE/2)
	  bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
	f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
	hd.cksize -= ret;
	audioplayerWhole = 0;
      }
    }
    audioplayerStop();
    printf("File played\n");
  }
   
  rc = f_close(&fid);
  printf("\nClose the file.\n");

  if (rc) die(rc);
  // while (1);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif


/* main.c ends here */
