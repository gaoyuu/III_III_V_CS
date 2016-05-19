/**********************************************************
 * f3d_user_btn.c
 * led display user input
 *
 * Author: gaoyu and Erik Bailey eribaile
 * Date Created: 2016/2/4 
 * Last Modified by: gaoyu and Erik Bailey eribaile
 * Date Last Modified: 2016/2/6 
 * Assignment: lab4
 * Part of: lab4
 *///


#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>


/*Initialization of the UserButton*/
void f3d_user_btn_init(void){
  
 GPIO_InitTypeDef GPIO_InitStructure;
 GPIO_StructInit(&GPIO_InitStructure);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
 GPIO_Init(GPIOA, &GPIO_InitStructure);
  
}

/*reads the User Button*/
int user_btn_read(void){
  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
}

