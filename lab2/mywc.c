/*******************************************
 *mywc.m

 *count lines, words and characters
 *  author: Yu Gao
 *  date created: 2016-1-21
 *  last modified by: Yu Gao
 *  date last modified: 2016-1-21
 *  part of: lab2
 */

#include <stdio.h>
#include <string.h>

int main() {
  	int lines = 0;
	int words = 0;
	int characters = 0; 
	int c;	//initializing origin counters
  while ((c = getchar()) != EOF) {
	characters++;
	if (c == '\n') {
	lines++;
	words++;
	}
	if (c == ' ' || c == '\t' || c ==  '\r' || c =='\f' || c=='\v') {
	words++;
		}
	}

  printf("%d,  ",lines);
  printf("%d,  ",words);
  printf("%d\n",characters);
}
