#ifndef CHOICE_H
#define CHOICE_H

typedef struct
{
    char command[256];          /* The inputed command that needs execution */
    char flags[50];         /* 50 chars */
} Choice;

void execute(Choice choice);
Choice parsing(char command[]);

#endif

