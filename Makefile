default: main

all: clean main 

main: main.c utilities.c choice.c 
	gcc main.c utilities.c choice.c -o main 

utilities: utilities.c utilities.h
	gcc utilities.c -o utilities

clean:
	rm -f main *~
