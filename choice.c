#include "utilities.h"
#include "choice.h"
/*
Execute
Input: the broken up command input
Output: void
This function calls fork and execve and creates the children processes
that run outside the parent.
*/

void execute(Choice choice)
{


	char *const newenvp[] = {NULL};
	int i;
	char *flags[choice.num_flags + 2]; 
	pid_t pid;
	int status;
	

	printf("choice.command = %s\n", *choice.command);


	//extracting commands, clearing out extra spaces we did not want
	for(i = 0; i <= choice.num_flags; i++)
	{
	    flags[i] = choice.command[i];
	    printf("i = %s\n", *(choice.command + i));
	}

	flags[i] = NULL;
	pid = fork();
	if(pid == 0)
	{
//	    execve(choice.command[0], flags, newenvp);
	    if (!execve(choice.command[0], flags, newenvp))
	    {
		printf("FAILED\n");
		//	_exit(1);
	    }
	}
	else{

	    if(!choice.runInBackground)
	    {
		waitpid(pid, &status, 0);
	    }
	}
	
	
}
/*
new_choice
Input: either the argument or the flag
Output: a new spot in the array for the command/flag
This is a helper function for the parsing function 
and allocates space for strings
*/
Choice new_choice(Choice create)
{

    int i;

    create.num_flags = 0;
    create.runInBackground = false;
    
    for(i = 0; i < BUFF_LEN; i++)
    {
	create.command[i] = malloc(20); // creates 20 max size of the string 
	//we need to free this later
    }
//    *(create.command[i]+1) = '\0';
	    
    return create;  

}

