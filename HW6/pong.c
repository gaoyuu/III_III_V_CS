#include "c335sim.h"
#include "rect.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>

#define PADDLE_MOVE_INCREMENT 3
#define PADDLE_HEIGHT 25
#define PADDLE_THICKNESS 3
#define BALL_DIM 3
#define EVENT_LOOP_TIME 20

rect_t left_paddle;
rect_t right_paddle;
rect_t ball;

int ball_vx = 1;
int ball_vy = 2;
char filename[30];

FILE *file;

/*The event loop that handles the key input*/
void event_loop(void) {
  static int paddle_left_move = 0; 
  static int paddle_right_move = 0;
  SDL_Event event;

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
 
  SDL_PollEvent(&event);
  switch(event.type) {
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = 0;
      break;
    case SDLK_DOWN:
      paddle_right_move = 0;
      break;
    case SDLK_a:
      paddle_left_move = 0;
      break;
    case SDLK_z:
      paddle_left_move = 0;
      break;
    default:
      break;
    }
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      paddle_right_move = -PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_DOWN:
      paddle_right_move = PADDLE_MOVE_INCREMENT;
      break;
    case SDLK_a:
      paddle_left_move = -PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_z:
      paddle_left_move = PADDLE_MOVE_INCREMENT; 
      break;
    case SDLK_q:
      printf("Q PRESSED - Exit Program\n");
      exit(0);
      break;
    case SDLK_n:
      getline(&line, &len, file) != -1;
      drawString(0, 10, line, WHITE, BLACK);
      break;
    default:
      break;
    }
    break;
  }
  if (paddle_left_move) {
    moveRect(&left_paddle, 0, paddle_left_move, BLACK);
  }
  if (paddle_right_move) {
    moveRect(&right_paddle, 0, paddle_right_move, BLACK);
  }
}

/*Where the collisions are handled*/
void pong_game(void) {
  int collision;

  drawString(40,60,"hit q to quit",WHITE,BLACK);
  redrawRect(&left_paddle);
  redrawRect(&right_paddle);
  event_loop();
  collision = moveRect(&ball, ball_vx, ball_vy, BLACK);

  switch (collision) {
  case COLLISION_TOP:
    ball_vy = -ball_vy;
    break;
  case COLLISION_BOTTOM:
    ball_vy = -ball_vy;
    break;
  case COLLISION_LEFT:
    ball_vx = -ball_vx;
    break;
  case COLLISION_RIGHT:
    ball_vx = -ball_vx;
    break;
  }
}

char *x,*y,*z;
void displayCoor(FILE *file){
  fscanf(file, "%s", &x);
  printf("%s",x);
  fscanf(file, "%s", &y);
  fscanf(file, "%s", &z);
  fillScreen(BLACK);
  drawString(30,90, "x: ", WHITE, BLACK);
  drawString(50,90, x, WHITE, BLACK);
  drawString(30,100, "y: ", WHITE, BLACK);
  drawString(50,100, y, WHITE, BLACK);
  drawString(30,110, "z: ", WHITE, BLACK);
  drawString(50,110, z, WHITE, BLACK);


}

//Where the pong_game() is called the rectangels are initialized.
int c335_main( int argc, char *argv[] ) {

  
  fillScreen(BLACK);
  initRect(&left_paddle,0,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE);
  initRect(&right_paddle,ST7735_width-PADDLE_THICKNESS,ST7735_height/2-(PADDLE_HEIGHT/2),PADDLE_THICKNESS,PADDLE_HEIGHT,WHITE);
  initRect(&ball,ST7735_width/2-(BALL_DIM/2),ST7735_height/2-(BALL_DIM/2),BALL_DIM,BALL_DIM,WHITE);

  strcpy(filename,argv[2]);
  file=fopen(filename,"r");
  displayCoor(file);
  
  while(1){
    pong_game();
    Delay(EVENT_LOOP_TIME);
  }
}
