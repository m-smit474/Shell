#include <stdio.h>
#include <unistd.h>
#include <string.h> // Need to remove at some point
#include <sys/types.h>
#include <sys/wait.h>

#include"utilities.h"
#include "choice.h"

void execute(Choice choice)
{
    char *fullCommand;
    
    strcat(fullCommand, choice.command); // might need a space
    strcat(fullCommand, choice.flags);
    
    char *const newargv[] = { choice.command, choice.flags, NULL };
    char *const newenvp[] = { NULL };

    printf("Im about to become: %s\n", choice.command);

    if(!execve( choice.command, newargv, newenvp))
    {
	// Failed to execute
	printf("FAILED\n");
    }

    // Does not reach
}

Choice parsing(char userInput[]){
    int i;
    int j;
    Choice parsnip;


    for(i=0; i< BUFF_LEN && userInput[i] != '\0' ; i++)
    {
    
	while(userInput[i] == ' ')
	    i++;
		
	if(userInput[i] == '/')
	{ 

	   
	    j=0;
	    while(userInput[i] != '\0' && userInput[i] != ' ')
	    {
	 
		parsnip.command[j] = userInput[i];
		j++;
		i++;

	    }
	    printf("Parsnip.command = %s\n",parsnip.command);

	    parsnip.command[j] = '\0';
	    
	    j=0;
	
	}

//	printf("WE MADE IT HERE\n");
	
	if(userInput[i] == '-')
	{
	    
	    while(userInput[i] != '\0' && userInput[i] != ' ')
	    {
		parsnip.flags[j] = userInput[i];
		j++;
		i++;
	    }
	    parsnip.flags[j] = ' ';
	    j++;
	    printf("Parsnip.flag = %s\n",parsnip.flags);


	}
	    
	   
    }
    return parsnip;
}
