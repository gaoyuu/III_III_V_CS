/* testvector.h --- 
 * 
 * Filename: testvector.h
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: Yu Gao
 * Created: Wed Oct  7 14:14:25 2015
 * Last-Updated: Mar 23 2016
 *           By: Yu Gao 

/* Code: */
#include <stdint.h>

enum {ADCS, ADDS, SUBS, ANDS, BICS, LSLS, ASRS, ALL};
typedef struct testvector {
  int32_t instruction;          // Specific instruction type
  int32_t rn;                   // Register where operand 1 should be stored
  int32_t rn_value;             // Value of operand 1   
  int32_t rm;                   // Register where operand 2 should be stored
  int32_t rm_value;             // Value of operand 2  
  int32_t expected_result;      // Expected resultant value of the operation
  int32_t previous_psr;         // Value of the PSR prior to instruction to test.  
  int32_t expected_psr;         // NZCV in upper nibble 
} testvector_t;

extern testvector_t vectors[];
void test_instructions(int);

/* testvector.h ends here */
