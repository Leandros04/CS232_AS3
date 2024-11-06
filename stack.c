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
STACK *initStack(){

    STACK *stack = (STACK *)malloc(sizeof(STACK)); //  Allocates memory for the stack.

    if(stack == NULL){

        printf("Error: Failed to allocate memorty for the stack.\n");
        exit(-1);

    }

    stack->top = NULL;
    stack->size = 0;

    return stack;
    
}

/**
 *  @brief Checks if the stack is empty.
 * 
 *  @param stack Pointer to the stack that will be checked if it is empty.
 * 
 *  @return Returns true if the stack is empty, else it returns false.
 * 
 */
bool isEmpty(STACK *stack){

    if(stack->size == 0 || stack == NULL) return true;

    else return false;

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
NODE *top(STACK *stack){

    if(isEmpty(stack) == true){

        printf("Error: The stack is empty.\n");
        return NULL;

    }

    else{

        return stack->top;
    
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
 * 
 */
void freeStack(STACK *stack) {

    if(stack == NULL){

        printf("Error: stack is empty. There is nothing to free\n");
        free(stack);
        return;

    }

    NODE *current = stack->top;

    while(current != NULL){

        NODE *next = current->next;

        //  Frees each row in the 2D array square, if it exists.
        if(current->square != NULL){

            for(int i=0; i<current->row; i++){

                free(current->square[i]);

            }

            free(current->square);

        }

        //  Frees the node itself.
        free(current);
        current = next;

    }

    free(stack); //  Frees the stack structure.

}

