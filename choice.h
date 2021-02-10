#ifndef CHOICE_FILE
#define CHOICE_FILE

typedef struct
{
    char command[256];          /* The inputed command that needs execution */
    char flags[10][50];         /* 10 flags of 50 chars */
} Choice;

#endif

