/**********************************************************
 * rpn calculatro.c
 *
 *
 * Author: gaoyu
 * Date Created: 2016/1/25
 * Last Modified by: 2016/1/25
 * Date Last Modified: 2016/1/25
 * Assignment: hw0
 * Part of: hw0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CELL* LIST;//typedef our CELL*

struct CELL {//A list as our stack
    int val;
    LIST next;
};

LIST stack; //initialize global data

void push(int val); //call functions ahead
int pop();
void first();

void main()
{
  int i,i1,i2; //i to judge if the input is number or operator,
               //i2,i3 is to restore 1st and 2nd numbers operated
  char input[127]; //get the user input

  LIST stack = NULL; //initialize data
  LIST tmp;

  while (*input != EOF && *input != 'q')//quit case
    {
    scanf("%s",input);
    i = atoi(input);
    if (strcmp(input, "0")==0 || i != 0) push(atoi(input));//if the input is # then push
    else {//else is an operator or a command
      switch (*input) {
    case 'p':
      first();
      break;
      case 'f': //print the whole data
      tmp = stack;
      while (tmp) {
	printf("%d\n",tmp->val);
	tmp = tmp->next;
	}
      break;
      case 'c': //delete until struct is empty
      while (stack) {
	pop();}
      break;
      case '+': // need at least 2 numbers to execute binary operators
      if (stack && stack->next) {
	i2 = pop();
	i1 = pop();
	push(i1 + i2);
      } else printf("not enough inputs\n");
      break;
    case '-':
      if (stack && stack->next) {
	i2 = pop();
	i1 = pop();
	push(i1 - i2);
      } else printf("not enough inputs\n");
      break;
    case '*':
      if (stack && stack->next) {
	i2 = pop();
	i1 = pop();
	push(i1 * i2);
	} else printf("not enough inputs\n");
      break;
    case '/':
      if (stack && stack->next) {
	i2 = pop();
	i1 = pop();
	push(i1 / i2);
	} else printf("not enough inputs\n");
      break;
    case 'q':
      break; 
    default:
      printf("wrong type");
      break;
    }
  
}
  }}

void first() { //not pop but just diplay the leftmost element
  LIST c = stack;
  if (stack)printf("%d\n",stack->val);
  else printf("dc: stack empty\n");
}

int pop() { //pop up the leftmost element
  LIST c = stack;
  if (c) {
    stack = stack->next;
    int val = c->val;
    free(c);
    return val;
  } else {
    printf("Stack is empty\n");
    exit(1);
     }
}

void push(int val) { //store data from left
  LIST c = (LIST) malloc(sizeof(struct CELL));
    if (c) {
      c->val = val;
      c->next = stack;
          stack = c;
      } else {
          perror("Memory error\n");
          exit(1);
      }
  }

/**void display() {
  top1 = top;
  if (top1 == NULL)
    {
      printf("Stack is empty");
      return;
    }
  while (top != NULL)
    {
      printf("%d\n",top1->val);
      top1 = top1->ptr;
    }
}

void destroy() {
  top1 =top;

  while (top != NULL)
    {
      top1 = top ->ptr;
      free(top);
      top = top1;
      top1 = top1->ptr;
    }
  free(top1);
  top = NULL;
}

void create() {
  top = NULL;
}**/
