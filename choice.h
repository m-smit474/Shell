#ifndef CHOICE_H
#define CHOICE_H

typedef struct
{
    char *command[BUFF_LEN + 1];          /* The inputed command that needs execution */
    int num_flags;
    
} Choice;

void execute(Choice choice);
Choice new_choice(Choice create);
Choice parsing(char command[]);

#endif

