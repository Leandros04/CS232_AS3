/**
 *  @mainpage Latin Square
 *  @file latinSolver.c
 *  @brief Automatic Latin Square game solver.
 * 
 *  This program implements the Latin Square game. It reads the Latin Square from a file
 *  and attemps to solve it using a backtracking algorithm.
 * 
 *  @author Christos Michael (ID: 1135102 / UC1070456)
 *          Leandros Antoniades (ID: 1119296 / UC1069738)
 * 
 *  @bug No known bugs.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "stack.h"

#define N 9 //  Max Latin Square the program can handle.(else if N > 9 the displayLatinSquare function does not work properly)

//  Function declarations.
bool readLatinSquare(FILE *infile, int size, int **square);
bool isSolved(int **square, int size);
void displayLatinSquare(int size, int **square);
bool findEmptyCell(int **square, int size, int *row, int *col);

/**
 *  @brief Reads the Latin Square from a file and checks if the starting
 *  Latin Square is in a valid state, or if it is solved.
 * 
 *  This function reads the Latin's square size and elements from an input file 
 *  and stores them in a 2D array.
 *  
 *  @param infile Pointer to the input file which has the Latin Square. 
 *  @param size The size of the Latin Square.
 *  @param square 2D array representing the Latin Square.
 * 
 *  @return Returns true if the starting Latin Square from the file is solved, else it returns false. 
 * 
 */
bool readLatinSquare(FILE *infile, int size, int **square) {
    int element;

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if(fscanf(infile, "%d", &element) != 1) {
                printf("Error: Cannot read square elements.\n");
                exit(-1);
            }

            if(abs(element) > size) { // Checks if the element is within the range of the square size.
                printf("Error: File contains invalid values.\n");
                exit(-1);
            }
            
            square[i][j] = element;
        }
    }

    //  Checks if there are any extra elements after the square
    int extraElement;
    if(fscanf(infile, "%d", &extraElement) == 1) {
        printf("File contains more data than expected.\n");
        exit(-1);
    }

    //  Checks that the starting latin square given inside the file is in a valid state(no duplicate elements in any row or column)
    //  This check if performed after the latin square had been read from the input file
    for(int i = 0; i < size; i++) {
        
        //  Checks for duplicate elements in the same row
        for(int j = 0; j < size-1; j++) {
            int element = abs(square[i][j]);

            for(int k = j + 1; k < size; k++) {
                if(element == abs(square[i][k]) && element != 0) {
                    printf("Error: Duplicate elements in row %d.\n", (i + 1));
                    exit(-1);
                }
            }
        }

        // Checks for duplicate elements in the same column
        for(int j=0; j<size-1; j++) {
            int element = abs(square[j][i]);

            for(int k=j+1; k<size; k++) {
                if(element == abs(square[k][i]) && element != 0) {
                    printf("Error: Duplicate elementS in column %d.\n",i+1);
                    exit(-1);
                }
            }
        }
    }

    bool solved = isSolved(square,size);

    return solved;
}

bool isSolved(int **square, int size){
    int count = 0; 
    
    //  Assuming that only a valid latin square is read from the file, if there are no emtpy cells 
    //  that means that the latinsquare is solved
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if(square[i][j] == 0) {
                count++;                
            }
        }
    }

    if(count == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 *  @brief Displays the Latin Square on the screen.
 * 
 *  This function displays the Latin Square on the screen within a border.
 *  
 *  @param size The size of the Latin Square.
 *  @param square 2D array representing the Latin Square.
 */
void displayLatinSquare(int size, int **square) {
    for(int i=0; i<size; i++) {
        //  Prints the lines of the square
        for(int j=0; j<size; j++) {
            printf("+-----");
        }

        printf("+");
        printf("\n");

        for(int j=0; j<size; j++) {
            if(square[i][j] < 0) {
                printf("| (%d) ", abs(square[i][j]));
            } else {
                printf("|  %d  ", square[i][j]);
            }
        }
        printf("|\n");
    }

    //  Prints the last line of the square
    for(int i=0; i<size; i++) {
        printf("+-----");
    }
    printf("+\n");
}

/**
 *  @brief Finds and returns the first empty cell of the current Latin Square.
 * 
 *  This function finds where an empty cell appears for the first time in the 
 *  current Latin Square and returns the row and column value of that cell.
 * 
 *  @param square 2D array representing the Latin Square.
 *  @param size The size of square array.
 *  @param row Pointer to the row of the first empty cell.
 *  @param col Pointer to the column of the first empty cell.
 * 
 *  @return Returns true if an empty cell was found, else it returns false. 
 * 
 */
bool findEmptyCell(int **square, int size, int *row, int *col) {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if(square[i][j] == 0) { //  If this is true that means an empty cell was found inside the array.
                *row = i;
                *col = j;
                return true;
            }
        }
    }
    return false;
}


void solveLatinSquare(int **square, int size){

    bool solved = false; //  Boolean to check if the Latin Square is solved.
    int row;
    int col;
    findEmptyCell(square,size,&row,&col);
    int steps = 0; //  Counter for the total steps.
    int pushCount = 0; //  Counter for pushes.
    int popCount = 0; //  Counter for pops.

    STACK *stack = initStack();

    while(solved == false){

        steps++;
        bool numberExists = false; //  Bool to check if there is a valid number to fill the empty cell.
        bool valid = true;
        int element = square[row][col]; //  Used to check if the number is bigger than the previously inserted number(used for backtracking case).
        int validNum = 0;

        for(int i=1; i<=size; i++){ //  For loop to check if there are any valid numbers to insert in the empty cell.

            valid = true;

            for(int j=0; j<size; j++){

                //  Case were the same number is already in the same row or column of the square.
                if(i == abs(square[j][col]) || i == abs(square[row][j])){

                    valid = false;
                    break; //  Breaks from the inner for loop.

                }  

            }

            if(i != element && valid == true){

                validNum = i;
                break;

            }

        }

        printf("VALID NUM = %d\n", validNum);
        if(valid == true && validNum > element){

            pushCount++;
            numberExists = true;
            square[row][col] = validNum;
            solved = isSolved(square,size);
            push(stack,square,size,row,col); //  Pushes the new square in the stack.
            findEmptyCell(square,size,&row,&col); //  Finds a new empty cell.
            printf("PUSH: STEP %d\n", steps);
            displayLatinSquare(size,square);

        }

        if(numberExists == false){

            if(stack->size == 0){

                printf("Error: There are no stages to backtrack to. The Latin Square is unsolvable.\n");
                exit(-1);

            }

            popCount++;
            NODE *poppedNode = pop(stack); //  Pops the previous state from the stack.

            //  Restores the 2D array from the popped node.(previous state)
            for(int i=0; i<poppedNode->row; i++){

                for(int j=0; j<poppedNode->col; j++){

                    square[i][j] = poppedNode->square[i][j];

                }
            }

            //  Updates the row and col to the position of the last placed number.
            row = poppedNode->row;
            col = poppedNode->col;

            //  Frees the memory of the popped node.
            for(int i=0; i<poppedNode->row; i++){
                
                free(poppedNode->square[i]);

            }
            
            free(poppedNode->square);
            free(poppedNode);

            printf("POP: STEP %d\n", steps);
            displayLatinSquare(size,square);

            printf("Backtracking to row: %d, col: %d\n", row, col);

        }

    }

    printf("PUSH NUM: %d\n", pushCount);
    printf("POP NUM: %d\n", popCount);

}

int main(int argc, char *argv[]) {
    if(argc > 2) { //  Checks if there are too many arguments.
        printf("Error: Too many arguments.\n");
        printf("Usage: ./latinSolver <input_file.txt>\n");
        exit(-1);
    } else if(argc < 2) { //  Checks if there are not enough arguments.
        printf("Error: Not enough arguments.\n");
        printf("Usage: ./latinSolver <input_file.txt>\n");
        exit(-1);
    }

    FILE *infile = fopen(argv[1], "r"); 
    int size;

    if(infile == NULL) { //  Checks if the input file was opened successfully.
        printf("Error: Failed to open the input file.\n");
        exit(-1);
    }

    if(fscanf(infile, "%d", &size) != 1) { //  Reads the size from the input file.
        printf("Error: Cannot read size.\n");
        exit(-1);
    }

    if(size < 1) { //  Checks if the size is valid.
        printf("Error: Not a valid square size.\n");
        exit(-1);
    }

    //  Creates a 2D dynamic square array.
    int **square = (int **)malloc(size*sizeof(int)); //  Allocates memory for each row pointer.

    if(square == NULL) { //  Checks if the memory was allocated successfully.
        printf("Error: Failed to allocate memory for the Latin Square.(rows)\n");
        exit(-1);
    }

    for(int i=0; i<size; i++) {     
        square[i] = (int *)malloc(size*sizeof(int)); //  Allocates memory for each column pointer.

        if(square[i] == NULL) { 
            printf("Error: Failed to allocate memory for the Latin Square (columns).\n");
            exit(-1);
        }
    }

    bool solved = readLatinSquare(infile,size,square);

    if(solved == false) {  //  If the starting Latin Square is not solved, the program will attempt to solve it.
        //  Testing displayLatinSquare function.
        displayLatinSquare(size,square);

        //  Testing findEmptyCell function.
        int row;
        int col;
        
        findEmptyCell(square,size,&row,&col);
        printf("Empty cell found at %d, %d\n", row,col);
    } else { //  If the starting Latin Square is solved there is no need to perform changes to it.
        printf("The Latin Square is already solved.\n");
    }

    fclose(infile);
    return 0;
}
