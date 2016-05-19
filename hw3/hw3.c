/**********************************************************
 * hw3.c
 *
 *   Author: Yu Gao
 ---
 *   Date Created: 2/28/2016
 ---
 *   Last Modified by: Yu Gao
 ---
 *   Date Last Modified: 2/28/2015
 ---
 *   Assignment: HW3
 ---
 *   Part of: hw3.c
 ---
 */

#include<stdio.h>

#define getOpcode1(x)(((x) >> 9) & 0x1) // the macro for getting the opcode for condition 2
#define getRm(x)(((x) >> 6) & 0x3) //macro for getting Rm
#define getRn(x)(((x) >> 3) & 0x3) // macro for getting Rn
#define getRd(x)(x & 0x3) // macro for getting Rd

#define getOpcode2(x)(((x) >> 6) & 0x4) // the macro for getting the Opcode for condition 5
#define getDataRm(x)(((x) >> 3) & 0x3) // the macro for getting the Rm
#define getRdn(x)(x & 0x3) // the macro for getting Rdn


int main(){
    int inst;
    char *opcodes1[] = {"adds", "subs"};
    char *opcodes2[] = {"ands", "eors", "lsls", "lsrs","asrs","adcs","sbcs","rors","tst","rsbs","cmp","cmn","orrs","muls","bics","mvns"};
    char *regnames[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7","r8","r9","r10","r11","r12","sp","lr","pc"};
    printf(".text\n.syntax unified\n.thumb\n");
    while (scanf("%x", &inst)==1){
        switch(inst>>10){
            case 6:
            printf("\t %s, %s, %s, %s \n", opcodes1[getOpcode1(inst)], regnames[getRm(inst)], regnames[getRn(inst)], regnames[getRd(inst)]);
                break;
            case 16:
            printf("\t %s, %s, %s\n", opcodes2[getOpcode2(inst)], regnames[getDataRm(inst)], regnames[getRdn(inst)]);
                break;
            default:
                printf("not legal number");
                break;
                
                
        }
    }
    
}
