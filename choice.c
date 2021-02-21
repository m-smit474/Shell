#include <stdio.h>
#include <unistd.h>
#include <string.h> // Need to remove at some point
#include <sys/types.h>
#include <sys/wait.h>

#include "utilities.h"
#include "choice.h"

void execute(Choice choice)
{

	//strcpy(fullCommand, choice.command); // add command to string

	/*
    for (i = 0; i < choice.num_flags; i++) // add flags to string
    {
	strcat(fullCommand, choice.flags[i]);
    }
    */

//	char *const newargv[] = {choice.command, NULL};
	char *const newenvp[] = {NULL};

//	printf("WE MADE IT HERE");
	printf("choice.command = %s\n", *choice.command);
	
	execve(choice.command[0], choice.command, newenvp);
	
	if (!execve(choice.command[0], choice.command, newenvp))
	{
		// Failed to execute
		printf("FAILED\n");
		_exit(1);
	}

	// Does not reach
}

Choice parsing(char userInput[])
{
	int i;
	int j;
	int k;
	Choice parsnip;
	char temp[BUFF_LEN + 1];
	
	for (i = 0, k = 0; i < BUFF_LEN && userInput[i] != '\0'; i++, k++)
	{
		while (userInput[i] == ' ')
		{
			i++;
		}

		j = 0;
		
//		parsnip.command[k] = &userInput[i];

		while(userInput[i] != '\n' && userInput[i] != ' ')
		{
		    printf("userInput = %s", &userInput[i]);
		    temp[j] = userInput[i];
		    j++;
		    i++;
		}
		
//		printf("\n");
		parsnip.command[k] = &temp[0];
//		strcpy(parsnip.command[k], *temp);
		printf("INSIDE = %s\n", *parsnip.command);

		
/*		for(j = 0; j < BUFF_LEN; j++)
		{
		    temp[j] = '\0';
		}
*/		
	}

	printf("AFTER FOR %s\n", *parsnip.command);


	return parsnip;
}
