# Latin Solver #

This is a C code that reads a Latin Square from an input file and attemps to solve it using a backtracking algorithm, and a stack. If the Latin Square is unsolvable it displays the suitable error messages. Also at the end of the program the total number of pushes in the stack and pops from the stack are displayed. (The max size of a Latin Square the program can handle is 9, else if a Latin Square bigger than size 9 is inputed the display of the Latin Square on the screen will not be alligned. The code will still work but the Latin Square will not be displayed correctly on the screen).

## Team Members ##

- **Leandros Antoniades** - ID: UC1069738
- **Christos Michael** - ID: UC1070456

## Files ##

- **stack.h**: Header file that has the stack data structure, the node data structure and the function declarations for the stack.

- **stack.c**: C file that has the implementations for the stack functions. These inlcude stack initialization, push, pop, get the top node from the stack and check if the stack is empty.

- **latinSolver.c**: C file that has the main code for solving the Latin Square using the backtracking algorirthm, and a stack.

## Usage ##

1. **Include the stack**: Include "stack.c" when compiling the program.

2. **Compile the program**:
```bash
gcc -o latinSolver latinSolver.c stack.c
```
or
```bash
make
```
3. **Run the program**:
```bash
./latinSolver <inputFile.txt>
```
When using this command the program will attempt so solve the Latin Square inside the input file.

---
_End of file_