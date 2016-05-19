/**********************************************************
* f3d_uart.h
*
*header file of user input and inter behavior
*
*   Author: Yu Gao
*   Date Created: 2016-1-21
*   Last Modified by: Yu Gao with robert Mulligan
*   Date Last Modified: 2016-2-11
*   Assignment: lab5
*   Part of: lab5
*/
/* Code: */
void f3d_uart_init(void);
void USART1_IRQHandler(void);
int putchar(int);
int getchar(void);
void flush_uart(void);
void putstring(char *);
