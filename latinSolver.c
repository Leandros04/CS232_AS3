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
* 
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"stack.h"

#define N 9 //  Max Latin Square the program can handle.(else if N > 9 the displayLatinSquare does not work properly)

//  Function declarations.
bool readLatinSquare(FILE *infile, int size, int **square);
bool isSolved(int **square, int size);
void displayLatinSquare(int size, int **square);
bool findEmptyCell(int **square, int size, int *row, int *col);
void solveLatinSquare(int **square, int size);

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
bool readLatinSquare(FILE *infile, int size, int **square){

   int element;

   for(int i=0; i<size; i++){

       for(int j=0; j<size; j++){

           if(fscanf(infile, "%d", &element) != 1){

               printf("Error! Cannot read square elements.\n");
               exit(-1);

           }

           if(abs(element) > size){

               printf("Error: File contains invalid values!\n");
               exit(-1);

           }

           square[i][j] = element;

       }

   }

   //  Checks if there are any extra elements after the square.
   int extraElement;
   if(fscanf(infile, "%d", &extraElement) == 1){

       printf("File contains more data than expected!\n");
       exit(-1);

   }

   //  Checks that the starting latin square given inside the file is in a valid state(no duplicate elements in any row or column)
   //  This check is performed after the latin square had been read from the input file
   for(int i=0; i<size; i++){
       
       //  Checks for duplicate elements in the same row
       for(int j=0; j<size-1; j++){

           int element = abs(square[i][j]);

           for(int k=j+1; k < size; k++){

               if(element == abs(square[i][k]) && element != 0){

                   printf("Error: Duplicate elements in row %d.\n",i+1);
                   exit(-1);
           
               }

           }

       }

       //  Checks for duplicate elements in the same column
       for(int j=0; j<size-1; j++){

           int element = abs(square[j][i]);

           for(int k=j+1; k<size; k++){

               if(element == abs(square[k][i]) && element != 0){

                   printf("Error: Duplicate elementS in column %d.\n",i+1);
                   exit(-1);
           
               }

           }

       }

   }

   bool solved = isSolved(square,size);

   return solved;

}

/** 
 *  @brief Checks if the Latin Square is solved.
 * 
 *  This function checks if the Latin Square is solved by checking if there are any empty squares.
 *  Assuming that only valid values were inserted in the Latin Square.
 * 
 *  @param square 2D array representing the Latin Square.
 *  @param size The size of the square array.
 * 
 *  @return Returns true if the Latin Square is solved, else it returns false.
 * 
 */
bool isSolved(int **square, int size){

   int count = 0; 
   
   //  Assuming that only valid Latin Square are read from the file if there are no emtpy cells that means that the Latin Square is solved
   for(int i=0; i<size; i++){

       for(int j=0; j<size; j++){

           if(square[i][j] == 0){

               count++;                
               
           }

       }

   }

   if(count == 0){

       return true;

   }
   else{

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
* 
*  @return Void.
*  
*/
void displayLatinSquare(int size, int **square){

   for(int i=0; i<size; i++){

       //  Prints the lines of the square
       for(int j=0; j<size; j++){

           printf("+-----");

       }

       printf("+");
       printf("\n");

       for(int j=0; j<size; j++){

           if(square[i][j] < 0){

               printf("| (%d) ", abs(square[i][j]));

           }
           else{

               printf("|  %d  ", square[i][j]);

           }

       }

       printf("|\n");

   }

   //  Prints the last line of the square
   for(int i=0; i<size; i++){

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
bool findEmptyCell(int **square, int size, int *row, int *col){

   for(int i=0; i<size; i++){
       
       for(int j=0; j<size; j++){

           if(square[i][j] == 0){ //  If this is true that means an empty cell was found inside the array.

               *row = i;
               *col = j;
               return true;

           }

       }

   }

   return false;

}

/**
 *  @brief Solves the Latin Square using a backtracking algorithm.
 * 
 *  This function solves a Latin Square using a backtracking algorithm and a stack. First it searches for an empty cell.
 *  Then it checks if there is a number that can be inserted in that cell and it does not break the rules of the game.
 *  If there is a valid number it is inserted in the Latin Square and pushed in the stack. If there is not a valid number the
 *  previous state of the Latin Square is popped from the stack and a new number will be found.
 *  If no number can be inserted in any cell then the Latin Square is unsolvable.
 * 
 *  @param square 2D array representing the Latin Square.
 *  @param size The size of the square array.
 * 
 *  @return Returns void.
 * 
 */
void solveLatinSquare(int **square, int size){

   bool solved = false; //  Boolean to check if the Latin Square is solved.
   int row; //  Row number of the empty cell.
   int col; //  Column number of the empty cell.
   findEmptyCell(square,size,&row,&col); //  Finds the first empty cell of the Latin Square.
   int steps = 0; //  Counter for the total steps.
   int pushCount = 0; //  Counter for pushes.
   int popCount = 0; //  Counter for pops.
   int prevNum = 1; //  Number that will be checked for insertion.

   STACK *stack = initStack();

   while(solved == false){

        steps++;
        int validNum; //  Variable to store the valid number that will be inserted in the empty cell.
        bool numberExists = false; //  Boolean to check if there is a valid number that can be inserted.

        for(int i=prevNum; i<=size; i++){ //  This for loop checks if there is a valid number that can be inserted in the current empty cell.

            bool found = true; //  Boolean to check if a valid number was found.

            for(int j=0; j<size; j++){ //  This for loop checks if the number can be inserted in the current empty cell.

                if(abs(square[j][col]) == i || abs(square[row][j]) == i){ //  Checks if the number is already in the same column or row.

                    found = false; //  Indicates that the number checked was not valid.
                    break;

                }

            }

            if(found == true){

                validNum = i;
                numberExists = true;
                break;

            }

        }

        if(numberExists == true){ //  A valid number was found, regular push.

            pushCount++;
            printf("PUSH: STEP %d\n", steps);
            square[row][col] = validNum; //  Updates the empty cell.
            push(stack,square,size,row,col);
            findEmptyCell(square,size,&row,&col); //  Finds the next empty cell of the Latin Square.
            displayLatinSquare(size,square);
            solved = isSolved(square,size);
            prevNum = 1; //  No backtrack case so start checking from value 1.

        }
        else{ //  A valid number was not found, backtrack case.

            if(stack->size == 0){ //  If there are no stages to backtrack to then there is no solution.

                if(steps == 1) displayLatinSquare(size,square);
                printf("THE LATIN SQUARE IS UNSOLVABLE!!\n");
                break;

            }

            popCount++;
            printf("POP: STEP %d\n", steps);

            NODE *poppedNode = pop(stack); //  Pops the previous state of the Latin Square from the stack.
            prevNum = poppedNode->square[poppedNode->row][poppedNode->col]; //  Gets the previously inserted number so the search can start from there.
            prevNum++;

            for(int i=0; i<size; i++){

                for(int j=0; j<size; j++){

                    square[i][j] = poppedNode->square[i][j]; //  Copies the previous state of the Latin Square.

                }

            }

            row = poppedNode->row; //  Row of the previously inserted cell.
            col = poppedNode->col; //  Column of the previously inserted cell. 

            for(int i=0; i<size; i++) free(poppedNode->square[i]);
            free(poppedNode->square);
            free(poppedNode);
            displayLatinSquare(size,square);

        }

   }

   printf("PUSH NUM: %d\n", pushCount);
   printf("POP NUM: %d\n", popCount);

   freeStack(stack,size); //  Frees the allocated memory for the stack.

}

/**
 *  @brief This is the main function of the latinSolver program.
 * 
 *  This function is used to read and solve the Latin Square and also display error messages where needed.
 * 
 *  @param argc The number of arguments in the command line.
 *  @param argv An array of strings containing the arguments in the command line.
 * 
 *  @return Returns 0 if the program was completed successfully.
 * 
 */
int main(int argc, char *argv[]){

   if(argc > 2){

       printf("Error: Too many arguments.\n");
       printf("Usage: ./latinSolver <input_file.txt>\n");
       exit(-1);

   }
   else if(argc < 2){

       printf("Error: Not enought arguments.\n");
       printf("Usage: ./latinSolver <input_file.txt>\n");
       exit(-1);

   }

   FILE *infile = fopen(argv[1], "r");
   int size;

   if(infile == NULL){

       printf("Error: Failed to open the input file.\n");
       exit(-1);

   }

   if(fscanf(infile, "%d", &size) != 1){ //  Reads the size from the input file.

       printf("Error: Cannot read size.\n");
       fclose(infile);
       exit(-1);

   }

   if(size < 1){

       printf("Error: Not a valid square size.\n");
       exit(-1);

   }

   if(size > N){
    
        printf("WARNING: THE SIZE IS TOO BIG, THE DISPLAY OF THE LATIN SQUARE MAY NOT WORK PROPERLY!!\n"); //  Warning in case of where the size given is bigger than what the display method can handle.
        char ans;
        while(1){ //  Infinite loop, until a valid answer was given.

            printf("Would you like to continue? [Y/N]");
            scanf(" %c", &ans); //  Reads the answer from the user.

            if(ans == 'Y') break; //  Breaks out of the infinite loop.
            else if(ans == 'N'){

                printf("Exiting the program...");
                exit(-1); //  Exits the program.

            } 
            else printf("Invalid input. Please enter 'Y' or 'N'.\n");

        }
        

    }

   //  Creates a 2D dynamic square array.
   int **square = (int **)malloc(size*sizeof(int *)); //  Allocates memory for each row pointer.

   if(square == NULL){

       printf("Error: Failed to allocate memory for the Latin Square.(rows)\n");
       fclose(infile);
       exit(-1);

   }

   for(int i=0; i<size; i++){

       square[i] = (int *)malloc(size*sizeof(int)); //  Allocates memory for each column pointer.

       if(square[i] == NULL){

            printf("Error: Failed to allocate memory for the Latin Square.(columns)\n");
            for(int j=0; j<i; j++) free(square[j]); //  Frees the already allocated memory.
            free(square);
            fclose(infile);
            exit(-1);

       }

   }

   bool solved = readLatinSquare(infile,size,square);

   if(solved == false){

       solveLatinSquare(square,size);

   }
   else{ //  If the starting Latin Square is solved there is no need to perform changes to it.

       printf("The Latin Square is already solved.\n");

   }

    //  Frees the allocated memory.
    for(int i=0; i<size; i++) free(square[i]); 
    free(square);

    fclose(infile);

    return 0;

}




