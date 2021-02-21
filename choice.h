#ifndef CHOICE_H
#define CHOICE_H

typedef struct
{
    char *command[BUFF_LEN + 1];          /* The inputed command that needs execution */

} Choice;

void execute(Choice choice);
Choice parsing(char command[]);

#endif

