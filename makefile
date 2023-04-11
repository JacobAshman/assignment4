#used as an easy way to compile the function
all: main.c functions.c functions.h #creates the main file
	gcc main.c functions.c functions.h -lm -o main