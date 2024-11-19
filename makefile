###############################################
# Makefile for compiling the program skeleton
# 'make'           build executable file 'PROJ'
# 'make doxy'      build project manual in doxygen
# 'make all'       build project + manual
# 'make clean'     removes all .o, executable and doxy log
###############################################

PROJ = latinSolver   # the name of the project
CC   = gcc           # name of compiler 
DOXYGEN = doxygen    # name of doxygen binary

# define any compile-time flags
CFLAGS = -std=c99 -Wall -O -Wuninitialized -Wunreachable-code -pedantic
LFLAGS = -lm

###############################################
# You don't need to edit anything below this line
###############################################

# list of object files 
C_FILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(C_FILES))

# To create the executable file, we need the object files
$(PROJ): $(OBJS)
	$(CC) -g -o $(PROJ) $(OBJS) $(LFLAGS)

# To create each individual object file
.c.o:
	$(CC) $(CFLAGS) -g -c $<

# To make all (program + manual) "make all"
all: 
	$(MAKE)
	$(MAKE) doxy

# To make the project documentation with Doxygen, enabling call graph and DOT graph generation
doxy:
	echo "CALL_GRAPH = YES" >> Doxyfile
	echo "HAVE_DOT = YES" >> Doxyfile
	$(DOXYGEN) Doxyfile &> doxygen.log

# To clean .o files: "make clean"
clean:
	rm -rf *.o doxygen.log html
