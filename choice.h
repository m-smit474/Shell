#ifndef CHOICE_H
#define CHOICE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> // Need to remove at some point
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>


typedef struct
{
    char *command[BUFF_LEN + 1];          /* The inputed command that needs execution */
    int num_flags;
    bool runInBackground;
    
} Choice;

void execute(Choice choice);
Choice new_choice(Choice create);
Choice parsing(char command[]);

#endif

