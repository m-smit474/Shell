#include <stdio.h>
#include <unistd.h>
#include <string.h> // Need to remove at some point
#include <sys/types.h>
#include <sys/wait.h>

#include"utilities.h"
#include "choice.h"

void execute(Choice choice)
{
    int i;
    char fullCommand[BUFF_LEN];

    strcat(fullCommand, choice.command); // add command to string

    for (i = 0; i < choice.num_flags; i++) // add flags to string
    {
	strcat(fullCommand, choice.flags[i]);
    }

    

    char *const newargv[] = {fullCommand, NULL };
    char *const newenvp[] = { NULL };
    


    if(!execve(choice.command, newargv, newenvp))
    {
	// Failed to execute
	printf("FAILED\n");
	_exit(1);
    }
  
    // Does not reach
}

Choice parsing(char userInput[]){
    int i;
    int j;
    int k;
    Choice parsnip;

    parsnip.num_flags = 0;
    k = 0;
    
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
	    
	
	}

//	printf("WE MADE IT HERE\n");
	
	if(userInput[i] == '-')
	{
	    
	    j=0;
	    while(userInput[i] != '\0' && userInput[i] != ' ')
	    {
		parsnip.flags[k][j] = userInput[i]; 
		j++;
		i++;
	    }
	    parsnip.flags[k][j] = '\0';
	    
	    parsnip.num_flags++;
	    k++;

	    
	    printf("Parsnip.flag = %s\n",parsnip.flags[k]);
//	    printf("Parsnip.flag j = %s\n",parsnip.flags[j]);
	    

	}
	    
	   
    }
    return parsnip;
}
