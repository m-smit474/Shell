default: main

all: clean main 

main: main.c utilities.c
	gcc main.c utilities.c -o main 

utilities: utilities.c utilities.h
	gcc utilities.c -o utilities

clean:
	rm -f main *~
