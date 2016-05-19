/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: Yu Gao
 * Created: Wed Oct  7 14:14:25 2015
 * Last-Updated: Mar 23 2016
 *           By: Yu Gao (with Bo Fang)

/* Code: */
#include <stdio.h> 
#include <stddef.h> 
#include <stdint.h> 
#include "testvector.h"
#include "machine.h"
#include "flags.h"

uint32_t reg[16];
uint32_t psr;
void LongLongAddition(char* rn, char* rm);
unsigned long long int converts_h(char* s);

int main(int argn, char** argm) {
  // Argument to test_instructions can be ALL to run all of tests or a specific
  // instruction can be tested by passing the name. 
  // ADCS, ADDS, SUBS, ANDS, BICS, LSLS, ASRS
  // To run the instruction tests for all of the instructions, pass ALL

  if(argn == 3) {
    LongLongAddition(*(argm+1), *(argm+2));
    return 0;
  }

  test_instructions(ANDS);
  test_instructions(ADCS);
  test_instructions(ADDS);
  test_instructions(BICS);
  test_instructions(LSLS);   
  test_instructions(ASRS);
return (0);
}

void ands(int rn, int rm) {
  // Include your code to emulate the "and" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

  reg[rn] &= reg[rm];

  // Negative Flag 
  if (reg[rn]&0x80000000) SET_N;
  else CLEAR_N;
 
  // Zero Flag 
  if (!reg[rn]) SET_Z;
  else CLEAR_Z;
}

void adcs(int rn, int rm) { 
  // Include your code to emulate the "adc" instruction: add with carry bits
  // adcs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]
  //initialize sign
  int rn_neg = 0;
  int rm_neg = 0;
  //check if rn and rm are negative
  if (reg[rn]&0x80000000) rn_neg = 1;
  if (reg[rm]&0x80000000) rm_neg = 1;
  reg[rn] += reg[rm];

  //compare the carry bit and add 1 if necessary

  if (psr & 0x20000000) reg[rn] += 0x00000001;
  //set negaive
  if (reg[rn]&0x80000000) SET_N;
  else CLEAR_N;
  //set zero
  if(!reg[rn]) SET_Z;
  else CLEAR_Z;
  //if rm and rn have same sign
  if (rm_neg == rn_neg) {
    //if rm and rn are positive
    if(rn_neg == 0) {
      //set carry flag
      if (reg[rn] < 0x00000000) SET_C;
      else CLEAR_C;
      //set overflow flag
      if (reg[rn]&0x80000000) SET_V;
      else CLEAR_V;
    }
    //if rm and rn are negative
    if(rn_neg == 1) {
      //set carry flag
      if (reg[rn] > 0x7FFFFFFF) SET_C;
      else CLEAR_C;
      //set overflow flag
      if (!(reg[rn]&0x80000000)) SET_V;
      else CLEAR_V;
    }
  }
  //if rm and rn are opposite sign and rn is positive, set carry flag
  if(rn_neg != rm_neg) {
    if(reg[rn] == 0) {
      SET_C;
    }
  }    
}

void adds(int rn, int rm) { 
    // Include your code to emulate the "add" instruction:
    // adds rn, rm
    // rn = index where operand1 is located in reg[], also destination for result
    // rm = index where operand2 is located in reg[]
  //initialize sign
    int rn_neg = 0;
    int rm_neg = 0;
    if (reg[rn]&0x80000000) rn_neg = 1; 
    if (reg[rm]&0x80000000) rm_neg = 1;
    reg[rn] += reg[rm];
    //set negative
    if (reg[rn]&0x80000000) SET_N;
    else CLEAR_N;
    //set sero
    if(!reg[rn]) SET_Z;
    else CLEAR_Z;
    //if rm and rn are same sign
    if (rm_neg == rn_neg) {
      //if rm and rn are positive
      if(rn_neg == 0) {
	//set carry flag
	if (reg[rn] < 0x00000000) SET_C;
	else CLEAR_C;
	//set overflow flag
	if (reg[rn]&0x80000000) SET_V;
	else CLEAR_V;
      }
      //if rm and rn are negative
      if(rn_neg == 1) {
	//set carry flag
	if (reg[rn] > 0x7FFFFFFF) SET_C;
	else CLEAR_C;
	//set overflow flag
	if (!(reg[rn]&0x80000000)) SET_V;
	else CLEAR_V;
	}
    }
    //if rm and rn are opposite sign and rn is positive, set carry flag
    if(rn_neg != rm_neg){
      if(reg[rn] == 0){
	SET_C;
      }
    }    
}

void bics(int rn, int rm) {
  // similar with ANDS
  reg[rn] = reg[rn] & ~(reg[rm]); 

  if (reg[rn]&0x80000000) SET_N;
  else CLEAR_N;
 
  if (!reg[rn]) SET_Z;
  else CLEAR_Z;
}
//lsls and asrs still have errors for strange cases,e.g in test vector 999 i dont know why 0x00000001
//shift right by 80 bits still get 0x00000001
void lsls(int rn, int rm) {
  int carry = 0;
  
  if (reg[rn]&(0x80000000 >> (reg[rm] -1))){
    SET_C;
    carry = 1;
  } else {CLEAR_C;}
  //action
  reg[rn] <<= reg[rm];
  //Allowed shifts 0-31. * C flag unaffected if shift is 0
  if(reg[rm] > 32){
    if(carry){//if it has carry
      CLEAR_C;
    } else {
      reg[rn] = 0x0;
    }
  }
  if (!reg[rn]) SET_Z;
  if (reg[rn]&0x80000000) SET_N;
}

void asrs(int rn, int rm) {
  if (reg[rm]) {
      if (reg[rn] >> (reg[rm] -1) & 1) SET_C;
      else CLEAR_C;
      //action
      reg[rn] = (int)reg[rn] >> reg[rm];
    }
  //for zero and negative flags the otherwise clear_cases, they wont affect psr,
  //but carry flag does.
  if (!reg[rn]) SET_Z;
  if (reg[rn]&0x80000000) SET_N;

}


//a function convert string to hex number:                                                                  
unsigned long long int converts_h(char* s){
  unsigned long long int n;
  s += 2;
  while(*s) {
    if(*s <= '9') n = n * 16 + *s - '0';
    else if(*s <= 'F') n = n * 16 + *s - 'A' + 10;
    else n = n * 16 + *s - 'a' + 10;
    s++;
  }
  return n;
}

void LongLongAddition(char* rn, char* rm) {

  unsigned long long int nhex,mhex;
  nhex = converts_h(rn);
  mhex = converts_h(rm);

  //divide input string to two 8-length hex number
  reg[0] = nhex >> 32;
  reg[1] = nhex;
  reg[2] = mhex >>32;
  reg[3] = mhex;
  //set nzcv
  psr = 0;
  adds(1,3);
  adcs(0,2);

  nhex = ((unsigned long long int)reg[0] << 32) + reg[1];
  printf("0x%.16lx\n", nhex);//result
}

