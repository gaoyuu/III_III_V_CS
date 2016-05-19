/* machine.h --- 
 * 
 * Filename: machine.h
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: Yu Gao
 * Created: Wed Oct  7 14:14:25 2015
 * Last-Updated: Mar 23 2016
 *           By: Yu Gao 

/* Code: */

extern uint32_t reg[16];
extern uint32_t psr;

void adds(int, int);
void subs(int, int);
void ands(int, int);
void bics(int, int);
void lsls(int, int);
void asrs(int, int);

/* machine.h ends here */
