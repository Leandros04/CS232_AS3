/**
 *  @mainpage Latin Square
 *  @file stack.h
 *  @brief Header file that implements a stack.\
 * 
 *  This program conatains all function declarations for the stack.
 * 
 *  @author Christos Michael (ID: 1135102 / UC1070456)
 *          Leandros Antoniadis (ID:  / UC )
 * 
 *  @bug No known bugs.
 * 
 */
#ifndef STACK_H
#define STACK_H

#include<stdbool.h>

/**
 *  @brief Represents a stack node.
 * 
 *  Each node has a 2D array of integers with dimensions row and column
 *  and a pointer to the next stack node. 
 * 
 */
typedef struct node{

    int **square; //  2D array representing the Latin Square.
    int row;
    int col;
    struct node *next;

}NODE;

/**
 *  @brief Represents a stack.
 * 
 *  A stack contains a pointer to the top node of the stack and the
 *  current size of the stack.
 * 
 */
typedef struct{

    NODE *top;
    int size;

}STACK;

//  Stack function declarations.
STACK *initStack();
bool isEmpty(STACK *stack);
void push(STACK *stack, int **square, int row, int col, int value);
NODE *pop(STACK *stack);
NODE *top(STACK *stack);
void freeStack(STACK *stack);

#endif
