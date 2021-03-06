#include "play.h"
#include "screen.h"
#include "tank.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <ff.h>
#include <math.h>
#include <string.h>
#include <stm32f30x.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_nunchuk.h>

Tank user;
Tank tanks[3];
Bull bullet[4];
uint8_t lives;
uint8_t positions[3][2] = {
  {0,0},
  {48,0},
  {112,0}
};
nunchuk_t n;

void user_event_loop(void) {
  static int user_v_move = 0;
  static int user_h_move = 0;
  f3d_nunchuk_read(&n);
  if(n.jy>150) {
    user_v_move = -TANK_V_INC;
    user_h_move = 0;
  } else if(n.jy<30) {
    user_v_move = TANK_V_INC;
    user_h_move = 0;
  } else user_v_move = 0;
  if(n.jx>150) {
    user_h_move = TANK_H_INC;
    user_v_move = 0;
  } else if(n.jx<30) {
    user_h_move = -TANK_H_INC;
    user_v_move = 0;
  } else user_h_move = 0;
  if(n.z)
    if(!(BULLU)) {
      initBull(&bullet[3],&user);
      lives|=0b1000000;
    }
  if (user_h_move||user_v_move) {
    moveTank(&user, user_h_move, user_v_move, BLACK);
  }
}

int kill,death;
void resetgame(void) {
  //f3d_lcd_fillScreen(BLACK);
  initTank(&user,USER_x,USER_y,0);
  user.head=0;
  drawTank(&user);
  drawMap();
  //Bullets and lives
  //  User B2 B1 B0 E2 E1 E0
  //0b0    0  0  0  0  0  0
  lives=0b0000000;
  kill=0;
  death=0;
}

void lose(void) {
  eraseTank(&user,BLACK);
  user.x=USER_x;
  user.y=USER_y;
  drawTank(&user);
  death++;
}
void goal(void) {
  kill++;
}

void tank_game(void) {

  char label[20]="Kill: ";
  char d[2];
  snprintf(d,3,"%.2d",kill);
  strcat(label,d);
  snprintf(d,3,"%.2d",death);
  strcat(label," Death: ");
  strcat(label,d);
  f3d_lcd_drawString(10,150,label,WHITE,BLACK);

  //0b  0  0  0  1
  //   -h +v +h -v
  static int tank_move0 = 0b0100;
  static int tank_move1 = 0b0100;
  static int tank_move2 = 0b0100;
  int result;

  if(ENEMY0) {
    if(tanks[0].x%16==0 && tanks[0].y%16==0 && ACTION)
      tank_move0 = 1<<(rand()%4);
    if(moveTank(tanks, tank_h(0), tank_v(0), BLACK)) {
      if(tanks[0].head%2==0) tank_move0 ^= 0b0101;
      else tank_move0 ^= 0b1010;
    }
    if(!(BULL0)) {
	initBull(bullet,tanks);
	lives|=0b0001000;
    } else {
      result=moveBull(bullet,BLACK);
      if(result) {
	eraseRect(&(bullet->ins),BLACK);
	lives&=0b1110111;
	if(result==2) {
	  //lose
	  lose();
	}
      }
    }
  } else {
    initTank(tanks,positions[0][0],positions[0][1],1);
    drawTank(tanks);
    lives|=1;
  }
  if(ENEMY1) {
    //if it is in a cell, it randomly change direction
    if(tanks[1].x%16==0 && tanks[1].y%16==0 && ACTION)
      tank_move1 = 1<<(rand()%4);
    //if it runs and hits other tanks, it go back
    if(moveTank(tanks+1, tank_h(1), tank_v(1), BLACK)) {
      if(tanks[1].head%2==0) tank_move1 ^= 0b0101;
      else tank_move1 ^= 0b1010;
    }
    if(!(BULL1)) {
	initBull(bullet+1,tanks+1);
	lives|=0b0010000;
    } else {
      result=moveBull(bullet+1,BLACK);
      if(result) {
	eraseRect(&((bullet+1)->ins),BLACK);
	lives&=0b1101111;
	if(result==2) {
	  //lose
	  lose();
	}
      }
    }
  } else {
    initTank(tanks+1,positions[1][0],positions[1][1],1);
    drawTank(tanks+1);
    lives|=2;
  }
  if(ENEMY2) {
    if(tanks[2].x%16==0 && tanks[2].y%16==0 && ACTION)
      tank_move2 = 1<<(rand()%4);
    if(moveTank(tanks+2, tank_h(2), tank_v(2), BLACK)) {
      if(tanks[2].head%2==0) tank_move2 ^= 0b0101;
      else tank_move2 ^= 0b1010;
    }
    if(!(BULL2)) {
	initBull(bullet+2,tanks+2);
	lives|=0b0100000;
    } else {
      result=moveBull(bullet+2,BLACK);
      if(result) {
	eraseRect(&((bullet+2)->ins),BLACK);
	lives&=0b1011111;
	if(result==2) {
	  //lose
	  lose();
	}
      }
    }
  } else {
    initTank(tanks+2,positions[2][0],positions[2][1],1);
    drawTank(tanks+2);
    lives|=4;
  }
  user_event_loop();
  if(BULLU) {
    result=moveBull(&bullet[3],BLACK);
    if(result) {
      eraseRect(&(bullet[3].ins),BLACK);
      lives&=0b0111111;
      if(result>=10) {
	result-=10;
	lives^=1<<result;
	eraseTank(tanks+result,BLACK);
	//goal
	goal();
      }
    }
  }
}

int pressed() {
  uint8_t count=0;
  while(1) {
    count++;
    while(!n.c && !n.z) f3d_nunchuk_read(&n);
    while(n.c || n.z) f3d_nunchuk_read(&n);;
    return count;
  }
}

int main(void) {

  f3d_lcd_init();
  f3d_lcd_fillScreen(WHITE); //set background  
  f3d_led_init();
  f3d_i2c1_init();
  delay(10);
  f3d_nunchuk_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);


  f3d_lcd_fillScreen(BLACK);
  f3d_lcd_drawString(32,100,"Tank Wars",WHITE,BLACK);
  f3d_lcd_drawString(22,130,"Press Z to Start",WHITE,BLACK);
  
  play();
  //use time of user's delay as random seed
  srand(pressed());
  f3d_lcd_drawString(32,100,"         ",WHITE,BLACK);
  f3d_lcd_drawString(22,130,"                ",WHITE,BLACK);

  resetgame();
  while (1) {
    tank_game();
    delay(EVENT_LOOP_TIME);
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif
