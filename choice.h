#ifndef CHOICE_H
#define CHOICE_H

typedef struct
{
    char command[256];          /* The inputed command that needs execution */
    char flags[10][50];         /* 10 flags of 50 chars */
} Choice;

#endif

