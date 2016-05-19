/* flags.h --- 
 * 
 * Filename: flags.h
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: Yu Gao
 * Created: Wed Oct  7 14:14:25 2015
 * Last-Updated: Mar 23 2016
 *           By: Yu Gao 

/* Code: */


#define CLEAR_Z psr &= ~(0x40000000) 
#define SET_Z psr |= 0x40000000

#define CLEAR_N psr &= ~(0x80000000)
#define SET_N psr |= 0x80000000

#define CLEAR_C psr &= ~(0x20000000)
#define SET_C psr |= 0x20000000

#define CLEAR_V psr &= ~(0x10000000)
#define SET_V psr |= 0x10000000

/* flags.h ends here */
