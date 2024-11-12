/**
 *  @mainpage Latin Square
 *  @file stack.c
 * 
 *  @author Christos Michael (ID: 1135102 / UC1070456)
 *          Leandros Antoniades (ID: 1119296 / UC1069738)
 * 
 *  @bug No known bugs.
 */
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

/**
 *  @brief Initializes a new empty stack.
 * 
 *  Allocates memory for a stack and initializes the stack's field.
 *  
 *  @return Returns a pointer to the stack. 
 * 
 */
STACK *initStack() { 

    STACK *stack = (STACK *)malloc(sizeof(STACK)); //  Allocates memory for the stack.

    if(stack == NULL) { //  Checks if the memory allocation was successful.
        printf("Error: Failed to allocate memorty for the stack.\n");
        exit(-1);
    }

    stack -> top = NULL;
    stack -> size = 0;

    return stack;
}

/**
 *  @brief Checks if the stack is empty.
 * 
 *  @param stack Pointer to the stack that will be checked if it is empty.
 * 
 *  @return Returns true if the stack is empty, else it returns false.
 */
bool isEmpty(STACK *stack) {
    if(stack -> size == 0 || stack == NULL) 
        return true;
    else 
        return false;
}

/**
 *  @brief Pushes a node inside the stack.
 * 
 *  This function pushes a node inside the stack and updates the fields of that node.
 * 
 *  @param stack A pointer to the stack.
 *  @param square 2D array representing the Latin Square.
 *  @param row Row where an element was last inserted.
 *  @param col Column where an element was last inserted.
 * 
 */
void push(STACK *stack, int **square, int size, int row, int col){

    NODE *p = NULL;
    
    if(stack == NULL){

        printf("Error: The stack is empty.\n");
        exit(-1);

    }

    p = (NODE *)malloc(sizeof(NODE)); //  Allocates memory for the new node.

    if(p == NULL){

        printf("Error: Failed to allocate memory for a new node.\n");
        exit(-1);

    }

    //  Allocates memory for the 2D array in the node.
    p->square = (int **)malloc(row*sizeof(int *));

    if(p->square == NULL){

        printf("Error: Failed to allocate memory for the 2D array.\n");
        free(p); //  Frees the new node.
        exit(-1);

    }

    //  Allocates memory for each row and copies the data.

    for (int i = 0; i < size; i++) {
        p->square[i] = (int *)malloc(size * sizeof(int));
        
        if (p->square[i] == NULL) {
            printf("Error: Failed to allocate memory for the 2D array row.\n");
            for (int j = 0; j < i; j++) {
                free(p->square[j]);
            }
            free(p->square);
            free(p);
            exit(-1);
        }

        // Copy data from the original array
        for (int j = 0; j < size; j++) {
            p->square[i][j] = square[i][j];
        }
    }

    p->row = row;
    p->col = col;
    p->next = stack->top;
    stack->top = p;
    stack->size++;
  
}

/**
 *  @brief Pops a node from the stack.
 * 
 *  This function pops a node from the stack and updates the stack's fields.
 * 
 *  @param stack A pointer to the stack.
 * 
 */
NODE *pop(STACK *stack){

    if(stack == NULL || stack->size == 0){

        printf("Error: The stack is empty. Cannot pop.\n");
        return NULL;

    }

    NODE *p = stack->top;
    stack->top = stack->top->next;
    stack->size--;

    return p;

}

/**
 *  @brief Returns the node at the top of the stack
 * 
 *  This function returns the top node of the stack without popping it 
 *  from the stack.
 * 
 *  @param stack A pointer to the stack.
 * 
 *  @return Returns NULL if the stack is empty, else it returns a pointer to the top node of the stack.
 * 
 */
NODE *top(STACK *stack) {
    if(isEmpty(stack) == true) {
        printf("Error: The stack is empty.\n");
        return NULL;
    } else {
        return stack -> top;
    }
}

/**
 *  @brief Frees all memory that was allocated for the stack.
 *
 *  This function iterates through the stack, freeing each node's `square` array
 *  and the nodes themselves. Finally, it frees the STACK structure.
 *
 *  @param stack A pointer to the stack to be freed.
 * 
 *  @return Returns void. 
 */
void freeStack(STACK *stack) {
    if(stack == NULL) {
        printf("Error: stack is empty. There is nothing to free.\n");
        return;
    }

    NODE *current = stack->top;

    while(current != NULL) {
        NODE *next = current->next;

        //  Frees each row in the 2D array square, if it exists.
        if(current -> square != NULL) {
            for(int i = 0; i < current -> row; i++) {
                free(current->square[i]);
            }

            free(current -> square); //  Frees the 2D array.
        }

        //  Frees the node itself.
        free(current);
        current = next;
    }

    free(stack); //  Frees the stack structure.
}
