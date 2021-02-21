#include <stdio.h>
#include <unistd.h>
#include <string.h> // Need to remove at some point
#include <sys/types.h>
#include <sys/wait.h>

#include "utilities.h"
#include "choice.h"

void execute(Choice choice)
{
	int i;
	char fullCommand[BUFF_LEN];

	//strcpy(fullCommand, choice.command); // add command to string

	/*
    for (i = 0; i < choice.num_flags; i++) // add flags to string
    {
	strcat(fullCommand, choice.flags[i]);
    }
    */

	char *const newargv[] = {fullCommand, NULL};
	char *const newenvp[] = {NULL};

	if (!execve(newargv[0], newargv, newenvp))
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

		printf("Made it to while 1\n");
		while (userInput[i] == ' ')
		{
			i++;
		}

		j = 0;
		printf("Made it to while 2\n");
		while (userInput[i] != '\n' && userInput[i] != ' ')
		{
			printf("Before parsnip.command\n");
			printf("%c\n", userInput[i]);
			temp[j] = userInput[i];
			printf("After parsnip.command\n");
			j++;
			i++;
		}
		// might need to do strcpy below
		parsnip.command[k] = temp;
	}

	return parsnip;
}
