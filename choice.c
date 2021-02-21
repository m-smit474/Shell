#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> // Need to remove at some point
#include <sys/types.h>
#include <sys/wait.h>

#include "utilities.h"
#include "choice.h"

void execute(Choice choice)
{

//	char *const newargv[] = {choice.command, NULL};
	char *const newenvp[] = {NULL};
	char *const newargv[] = {choice.command[0], choice.command[1],choice.command[2], NULL};
	int i;
	char *flags[choice.num_flags + 2]; 
	
//	printf("WE MADE IT HERE");
	printf("choice.command = %s\n", *choice.command);

	for(i = 0; i <= choice.num_flags; i++)
	{
	    flags[i] = choice.command[i];
	    printf("i = %s\n", *(choice.command + i));
	
	}

	flags[i] = NULL;

//	execve(choice.command[0], choice.command[i], newenvp);
	
	if (!execve(choice.command[0], flags, newenvp))
	{
		// Failed to execute
		printf("FAILED\n");
		_exit(1);
	}

	// Does not reach
}

Choice new_choice(Choice create)
{

    int i;

    create.num_flags = 0;
    
    for(i = 0; i < BUFF_LEN; i++)
    {
	create.command[i] = malloc(20); // creates 20 max size of the string 
	//we need to free this later
    }
//    *(create.command[i]+1) = '\0';
	    
    return create;  

}


Choice parsing(char userInput[])
{
	int i;
	int j;
	int k;
	Choice parsnip;
	char temp[BUFF_LEN + 1];

	parsnip = new_choice(parsnip);
	
	for (i = 0, k = 0; i < BUFF_LEN && userInput[i] != '\0'; i++, k++)
	{

	    while (userInput[i] == ' ')
	    {
		i++;
	    }

	    j = 0;

	    while(userInput[i] != '\n' && userInput[i] != ' ')
	    {

		*(parsnip.command[k] + j) = userInput[i];
		j++;
		i++;
	    }
		
	}


	parsnip.num_flags = k - 1;
//	printf("num_flags = %d\n", parsnip.num_flags);
	
	return parsnip;
}
