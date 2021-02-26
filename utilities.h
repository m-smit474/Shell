#ifndef UTILITIES_H
#define UTILITIES_H

// utilities class are functions we use multiple throughout
// the program

#define BUFF_LEN 256 // buffer length
#define WRITE 1
#define READ 0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>

#include "choice.h"


Choice parsing(char userInput[], int *i);
void prompt(char command[BUFF_LEN]);
int compare_strings(const char *string1, const char *string2);




#endif 
