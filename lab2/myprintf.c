/**********************************************************
* myprintf.c
*
* my printf version
*
*   Author: Yu Gao
*   Date Created: 2016-1-21
*   Last Modified by: YU Gao
*   Date Last Modified: 2016-1-21
*   Assignment: lab2
*   Part of: lab2
*/

#include <stdarg.h>
#include <stdio.h>


void printint(int i){//return integer
	printf("%d",i);
}
void printstring(char* c){//return char
	printf("%s",c);
}
void printhex(int e){//return hexadecimal
	printf("%x",e);
}
void myprintf(const char *fmt, ...) {
    const char *p;
    va_list argp;
    int i;
    char *s;

    va_start(argp, fmt);

    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'c':
            i = va_arg(argp, int);
            putchar(i);
            break;

        case 'd':
            i = va_arg(argp, int);
            printint(i);
            break;

        case 's':
            s = va_arg(argp, char *);
            printstring(s);
            break;

        case 'x':
            i = va_arg(argp, int);
            printhex(i);
            break;

        case '%':
            putchar('%');
            break;
        }
    }
    va_end(argp);
}


