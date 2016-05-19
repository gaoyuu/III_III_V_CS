/**********************************************************
* gcd.s
*
*   Author: Yu Gao(work with shichao hu)
---
*   Date Created: 4/4/16
---
*   Last Modified by: Yu Gao
---
*   Date Last Modified: 4/4/16
---
*   Assignment: Hw5
---

note:
b: unconditional branch
bne:branch if not equal
beq:branch if equal
bgt:branch if greater than
bit:branch if less than
*/
	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}	//register r0 = a;r1 = b; r2 =d
	movs r2, #0	//r2=d=0
	movs r4, #1	//r4=1
.WHILE:	//while
	movs r3, r0    	//r3=a
	ands r3, r4	//(a&1)
	bne .THEN	//not equal then branch to then

	movs r3, r1	//r3=b
	ands r3, r4	//(b&1)
	bne .THEN	//not equal then branch to then
	
	asrs r0, #1 	//a>>=1
	asrs r1, #1	//b>>=1
	adds r2, #1	//d+=1
	b .WHILE	//while loop

.THEN://second while loop

.WHILE1:
	cmp r0, r1 	//compare a and b
	beq .EXIT//branch if a and b equal

	movs r3, r0	//r3 = a;
	ands r3, r4	//(a&1)
	bne .IF		//branch to if if not equal

	asrs r0, #1   	//a>>=1
	b .WHILE1		//go back to while1 loop
.IF:
	movs r3, r1	//r3=b
	ands r3, r4	//(b&1)
	bne .ELSEIF	//go to first if
	
	asrs r1, #1	//if b is odd,b>>=1
	b .WHILE1	//while1 loop
.ELSEIF:
	movs r3, r1	//r3=b
	ands r3,r4	//(b&1)
	bne .ELSEIF1	//go to second elseif 

	asrs r1, #1	//if b is odd, b>>=1
	b .WHILE1	//go to second while
.ELSEIF1:
	subs r3, r0, r1	//a>b then r3=a-b 
	ble .ELSE	//b>a then go to else
	
	asrs r3, #1	//a
	movs r0, r3	//r3=a
	b .WHILE1	//go to second while
.ELSE:
	subs r3, r1, r0	//a=(b-a)
	asrs r3, #1	//a>>1
	movs r1, r3	//b=b-a
	b .WHILE1	//go to second while
	
.EXIT:
	lsls r0, r2	//logic shift left

	pop {r4-r7}
	bx	lr
