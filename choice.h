#ifndef CHOICE_H
#define CHOICE_H

#define READ_END 0
#define WRITE_END 1

typedef struct
{
    char *command[BUFF_LEN + 1];          /* The inputed command that needs execution */
    int num_flags;
    bool runInBackground;
    bool isPipe;
    
} Choice;

void launch(char userInput[]);
void execute(Choice choice);
Choice new_choice(Choice create);


#endif

