/**********************************************************
* abs.s
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
	take absolute value of a number
*/


	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}
	cmp r0, 0//check the number of sign
	bgt .END
	movs r1 , 0
	subs r0, r1, r0//subtract value form 0 if it is negative

.END:	
	pop {r4-r7}	
	bx	lr
