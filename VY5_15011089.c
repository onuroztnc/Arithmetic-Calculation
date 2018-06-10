//
//  main.c
//  VeriYapılariOdev5
//
//  Created by Onur Öztunç on 9.06.2018.
//  Copyright © 2018 Onur Öztunç. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100

typedef struct{
  char key;
  int value;
}HashMap;

/**
* The function that finds the position of the searched variable in the variable of array.
*/

int searchHashMap(HashMap *variable,int variable_size,char tempKey){
  int i=0;
  while (i<variable_size && variable[i].key!= tempKey) {
    i++;
  }
  if (i<variable_size)
    return i;
  else
    return -1;
}

/**
* This function adds the variable and value to the array.
*/

HashMap* HashMap_put(HashMap *variable,int *variable_size,char key,int value){
  if (searchHashMap(variable,*variable_size,key)!=-1) {
    int index = searchHashMap(variable,*variable_size,key); //If the variable is defined,
    variable[index].value = value;                         // the value is updated.
  }
  else{ // new variable is being created.
    *variable_size+=1;
    variable = (HashMap *)realloc(variable,sizeof(char)*(*variable_size));
    variable[*variable_size-1].key = key;
    variable[*variable_size-1].value = value;
  }
  return variable;
}

/*
* This function returns the value of the variable.
*/
int HashMap_get(HashMap *variable,int variable_size,char key){
  if (searchHashMap(variable,variable_size,key)!=-1) {
    int index = searchHashMap(variable,variable_size,key);
    return variable[index].value;
  }
  else{
    printf("Variable not defined.\n" );
    return -1;
  }
}

typedef struct{

  int top;
  int array[SIZE];

}Stack;

/**
* This function is checking that the Stack is full.
*/

int isFull(Stack *stack){
  if (stack->top == SIZE) {
    printf("Stack is full!\n");
    return 1;
  }
  return 0;
}

/**
* This function is checking that the Stack is empty.
*/

int isEmpty(Stack *stack){
  if (stack->top == 0) {
    printf("Stack is empty\n");
    return 1;
  }
  return 0;
}

/**
* This function is adding elements to the stack.
*/

void push(Stack *stack,int value){
  if (!isFull(stack)) {
    stack->array[stack->top] = value;
    stack->top+=1;
  }
}

/**
* This function is deleting elements to the stack.
*/

int pop(Stack *stack){
  int value=-1;
  if (!isEmpty(stack)) {
    value = stack->array[stack->top-1];
    stack->top-=1;
  }
  return value;
}

/**
* This function converts a string to a integer
*/

int strToInt(char *buffer,int *index,int buffer_size){
  int factor = 1;
  int result = 0;
  while (buffer[*index]<='9' && buffer[*index]>='0' && (*index)<buffer_size) {
    result *=factor;
    result += (buffer[*index]-'0');
    factor = 10;
    (*index) +=1;
  }
  return result;
}

/**
* This function prints the stack.
*/

void printStack(Stack stack){
  int i;
  printf("Stack: ");
  for (i = 0; i < stack.top ; i++) {
    printf("%d ",stack.array[i]);
  }
  printf("\n");
}

/**
* This function prints the given arithmetic expression.
*/
void printArithmeticExpression(char *buffer){
  int i=0;
  printf("Arithmetic Expression: ");
  while (buffer[i]!=';') {
    printf("%c",buffer[i]);
    i++;
  }
  printf(";\n");
}

/**
* This function prints intermediate operations.
*/

void intermediateOperations(char *postfix,int postfix_size,Stack stack){
  int i;
  printf("Postfix: ");
  for (i = 0; i < postfix_size; i++) { // print postfix notation
      printf("%c",postfix[i]);
  }
  printf("          Stack: ");
  for (i = 0; i < stack.top ; i++) { // print the current state of the stack
    printf("%c",stack.array[i]);
  }
  printf("\n");
}

/**
* This function sets the priority of arithmetic operations.
*/

int operatorPrecedence(char arithmetic){
  int temp;
  switch (arithmetic) {
    case '*': // '*' and '/' have the same priority.
    temp = 1;
    break;
    case '/':
    temp = 1;
    break;

    case '-': // '-' and '+' have the same priority.
    temp = 2;
    break;

    case '+':
    temp = 2;
    break;

    default: break;
  }

  return temp;
}

/**
* This function calculates the result of the arithmetic operation as the result of the two values ​​entered.
*/

int arithmeticOperation(int operand1,int operand2,char arithmeticOperator){

  if(arithmeticOperator == '*')
    return operand1*operand2;
  if (arithmeticOperator == '/') {
    return operand1/operand2;
  }
  if (arithmeticOperator == '-') {
    return operand1-operand2;
  }
  if (arithmeticOperator == '+') {
    return operand1+operand2;
  }
  printf("Incorrect operator");
  return -1;
}

/*
* The function that increments the size of the array for each new element and appends to it.
*/

char * rellocation(char *array,int *array_size,char newChar){
  char *newArray;
  *array_size += 1 ; //Increased for a new element
  newArray = (char *) realloc(array,(*array_size)*sizeof(char));
  newArray[*array_size-1] = newChar; // New element added
  return newArray;
}

/*
* This function converts the arithmetic expression from infix form to postfix form.
*/

char * infix_to_postfix(char *infix ,int *size){
  char *postfix; // The array defined for the Postfix form
  int postfix_size=0; // Number of elements in postfix array
  char last_arithmetic; // Last arithmetic expression pushed to the stack
  Stack stack;
  stack.top=0;
  postfix = (char *)malloc(sizeof(char)); //Postfix array allocation
  int i=0;

  while (infix[i]!=';') { //Until the end of the arithmetic term
    if ((infix[i]>='0' && infix[i]<='9') || (infix[i]>='A' && infix[i]<='Z') || (infix[i]>= 'a' && infix[i] <= 'z') ) {
      postfix = rellocation(postfix,&postfix_size,infix[i]); // If the number or variable comes in,
      intermediateOperations(postfix,postfix_size,stack);   //  it is added to the postfix array.
    }
    else if(infix[i] == ' '){
      postfix = rellocation(postfix,&postfix_size,infix[i]); // ' ' character is added to the postfix array.
    }
    else if (infix[i]=='(') {
      push(&stack,'(');                                    //If '(' character comes to the character,
      intermediateOperations(postfix,postfix_size,stack); //  it is pushed to the stack.
    }
    else if(infix[i]==')'){
      last_arithmetic = pop(&stack);
      while (last_arithmetic!='(') {
        postfix = rellocation(postfix,&postfix_size,last_arithmetic);
        last_arithmetic = pop(&stack);
      }
      intermediateOperations(postfix,postfix_size,stack);
    }
    else if(stack.top>0){   // Checking that the stack is not empty.
      last_arithmetic = pop(&stack);
      if ((operatorPrecedence(last_arithmetic) <= operatorPrecedence(infix[i])) && last_arithmetic!='(') {
        postfix = rellocation(postfix,&postfix_size,last_arithmetic); //The priorities of the new arithmetic operator
        push(&stack,infix[i]);                                        //are compared with the arithmetic operator in the stack.
        intermediateOperations(postfix,postfix_size,stack);
      }
      else{
        push(&stack,last_arithmetic);
        push(&stack,infix[i]);
        intermediateOperations(postfix,postfix_size,stack);
      }
    }
    else{ // If stack is empty , new arithmetic operator is pushed to stack
      push(&stack,infix[i]);
      intermediateOperations(postfix,postfix_size,stack);
    }
    i++;

  }
  while (stack.top > 0) { //The rest of the stack is added to postfix array.
    postfix = rellocation(postfix,&postfix_size,pop(&stack));
    intermediateOperations(postfix,postfix_size,stack);
  }
  *size = postfix_size;
  postfix = rellocation(postfix,&postfix_size,'\0');
  printf("Intermediate output: %s\n", postfix);
  return postfix;
}
/**
* This function allows the postfix form to be decoded.
*/

int result(HashMap *variable,int *variable_size,char *postfix,int postfix_size){
  int i=0;
  Stack stack;
  stack.top = 0;
  while (i<postfix_size) {
    if (postfix[i]>='0' && postfix[i]<='9') { // If the number comes, it pushes it to the stack.
        int value = strToInt(postfix,&i,postfix_size); // Strings translates to integers
        push(&stack,value);
        printStack(stack);
        i--;
    }
    else if ((postfix[i]>='A' && postfix[i]<='Z') || (postfix[i]>='a' && postfix[i]<='z')) {
        int value = HashMap_get(variable,*variable_size,postfix[i]); // If the variable name is comes,
        push(&stack,value);                                          //it takes its value from variable array and
        printStack(stack);                                           // pushes it to the stack.
    }
    else if (postfix[i]!=' ') {       // If arithmetic operator is comes,
      int operand2 = pop(&stack);     // It is taking the values ​​from the stack and
      int operand1 = pop(&stack);     // doing the operation.
      int value =arithmeticOperation(operand1,operand2,postfix[i]);
      push(&stack,value);             // Resultant pushes to stack.
      printStack(stack);
    }
    i++;
  }
  return pop(&stack);
}


int main(int argc, const char * argv[]) {
    FILE *finput;
    char buffer[1024];
    HashMap *variable; // The array where the variables are stored.
    int variable_size = 0;
    char key; // Variable name
    int value; // Value of the variable
    finput = fopen("input.txt","r");
    variable = (HashMap *)malloc(sizeof(HashMap));

    while (!feof(finput)) {
      char *postfix=NULL;
      int postfix_size;

      memset(buffer,0,1024);
      fgets(buffer , 1024 , finput);
      printArithmeticExpression(buffer);

      key= buffer[0]; // The first value of the arithmetic statement is variable.
      postfix = infix_to_postfix(&buffer[4],&postfix_size);

      value = result(variable,&variable_size,postfix,postfix_size);
      printf("%c <- %d\n\n",key,value);

      HashMap_put(variable,&variable_size,key,value); // Variable values ​​are being updated.
      free(postfix);
    }

    int i;
    printf("\nResult:\n");
    for (i = 0; i < variable_size; i++) {
      printf("%c = %d\n",variable[i].key,variable[i].value);
    }
    fclose(finput);
    free(variable);
    return 0;
}
