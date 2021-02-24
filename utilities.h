#ifndef UTILITIES_H
#define UTILITIES_H

#define BUFF_LEN 256
#define WRITE 1
#define READ 0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> // Need to remove at some point
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "choice.h"


Choice parsing(char userInput[], int *i);
void read_write(char command[BUFF_LEN]);
int compare_strings(const char *string1, const char *string2);
void choice(char command[]);



#endif 
