/**********************************************************
* fib.s
*
*   Author: Yu Gao
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
	.global	fib	
	.type fib, %function
fib:
	push {r4-r7}
	//movs r0, #0
	movs r1,#1 //prev2
	movs r2,#1 //pre1
	movs r3,#1 //val
	movs r4,#0 //i

	cmp r0, #0
	beq .END0
	cmp r0, #1
	beq .END1
	cmp r0, #2
	beq .END1
	b .THEN
.THEN:
	adds r3, r2, r1
	movs r1, r2
	movs r2, r3
	adds r4,r4, #1
	b .ELSE
.ELSE:
	subs r5, r0, #2
	cmp r4, r5
	blt .THEN
	b .END
.END://base case larger than 2
	movs r0, r3
	pop {r4-r7}
	bx lr
.END0://base case 0
	movs r0, #0
	pop {r4-r7}
	bx lr
.END1://base case 1 and 2
	movs r0, #1
	pop {r4-r7}
	bx	lr			
