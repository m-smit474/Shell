#include <stdio.h>
#include <unistd.h>
#include <string.h> // Need to remove at some point
#include"utilities.h"
#include "choice.h"

void execute(Choice choice)
{
    char *path = "/usr/bin/";
    strcat(path,choice.command);
    
    char *const newargv[] = { path, NULL };
    char *const newenvp[] = { NULL };

    if(!execve( path, newargv, newenvp))
    {
	// Failed to execute
    }

    // Does not reach
}

Choice parsing(char userInput[]){
    int i;
    int j;
    Choice parsnip;
    for(i=0; i< BUFF_LEN; i++)
    {
    
	while(userInput[i] == ' ')
	    i++;
		
	if(userInput[i] == '/')
	{ 

	    printf("User input was %c\n", userInput[i]);
	    
	    while(userInput[i] != ' ')
	    {
		j=0;
		parsnip.command[j] = userInput[i];
		j++;
		i++;
	    }
	    printf("Parsnip.command = %s\n",parsnip.command);
	    j=0;
	
	}

	if(userInput[i] == '-')
	{

	    while(userInput[i] != ' ')
	    {
		parsnip.flags[j] = userInput[i];
		j++;
		i++;
	    }
	}
	    
	   
    }
    return parsnip;
}
