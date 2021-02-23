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

/*
Parsing
Input: The command line that has been preprocessed by the readwrite function
Output: An array list with the first element being the command and remaining elements being the flags
The main for loop cycles through each character until the end of the input, 
the key part in this function is line *(parsnip.command[k] + j) = userInput[i] 
which sends either the command or the flag into the array.
*/

Choice parsing(char userInput[])
{
	int i;
	int j;
	int k;
	Choice parsnip;
	char temp[BUFF_LEN + 1];
	bool isWord;

	parsnip = new_choice(parsnip);

	for (i = 0, k = 0; i < BUFF_LEN && userInput[i] != '\0' && userInput[i] != '\n'; i++)
	{
		isWord = false;

	    while (userInput[i] == ' ')
	    {
		i++;
	    }

	    if(userInput[i] == '&')
	    {
		parsnip.runInBackground = true;
		i++;
	    }

	    j = 0;

	    while(userInput[i] != '\n' && userInput[i] != ' ')
	    {
		isWord = true;
		*(parsnip.command[k] + j) = userInput[i];
		j++;
		i++;
	    }
		if(isWord)
		k++;
	}


	parsnip.num_flags = k - 1;
//	printf("num_flags = %d\n", parsnip.num_flags);
	
	return parsnip;
}
