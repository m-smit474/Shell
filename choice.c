#include <signal.h>

#include "utilities.h"
#include "choice.h"

/*
launch

Input: the user command.
Output: none

This function executes the pipe if user inputs '|' char, else 
it runs the execve command normally.

*/
void launch(char userInput[])
{
    
    int *i;
    Choice parsnip, parsnip2;
    int pipefd[2];
    int pid1,pid2;
    int child_status;
    
    i = malloc(4);
    
    *i = 0;

    parsnip = parsing(userInput, i);

    if(parsnip.isPipe == true)
    {
//	printf("i inside if in launch = %d\n", *i);
	parsnip2 = parsing(userInput, i);

	if(pipe(pipefd) == -1)
	{
	    perror("pipe");
	    _exit(1);
	}
	
	pid1 = fork();
	if(pid1 == 0)
	{
	    close(pipefd[READ_END]);
	    dup2(pipefd[WRITE_END], 1);
	    execute(parsnip);
	    kill(getpid(), SIGKILL);
	}
	
	close(pipefd[WRITE_END]);

	pid2 = fork();
	if(pid2 == 0)
	{
	    close(pipefd[WRITE_END]);
	    dup2(pipefd[READ_END], 0);
	    execute(parsnip2);
	    kill(getpid(), SIGKILL);
	}
	
	close(pipefd[READ_END]);

	waitpid(pid1, &child_status, 0);
	waitpid(pid2, &child_status, 0);
	
    }
    else if(parsnip.inputRedirect || parsnip.outputRedirect)
    {
	
	redirect(parsnip);
	printf("AFTER REDIRECT IN LAUNCH\n");
//	execute(parsnip);
	printf("AFTER REDIRECT EXECUTE\n");
	
    }
    else
    {
	execute(parsnip);
    }
    
}

//comment help stackover flow.
void redirect(Choice parsnip)
{
    int in_fd, out_fd;
    int pid,pid2;
    int child_status;

    if(parsnip.inputRedirect)
    {
	
	pid = fork();
	if(pid == 0)
	{
	    in_fd = open(parsnip.fileName, O_RDONLY);
	    if(in_fd < 0)
	    {
		perror("failed to open file\n");
		_exit(1);
	    }
	    dup2(in_fd, STDIN_FILENO);
	    close(in_fd);
	    execute(parsnip);
	    kill(getpid(), SIGKILL);
	}

    }
    else // output redirect
    {
	pid2 = fork();
	if(pid2 == 0)
	{
//	    out_fd = creat(parsnip.fileName, 0644); //create
	    out_fd = open(parsnip.fileName, O_CREAT | O_RDWR | O_APPEND,0644); //create new output
	    if(out_fd < 0)
	    {
		perror("failed to create output file.\n");
		_exit(1);
	    }
	    dup2(out_fd, STDOUT_FILENO);
	    close(out_fd);
	    execute(parsnip);
	    kill(getpid(), SIGKILL);
	}
		
    }    

    waitpid(pid, &child_status, 0);
    waitpid(pid2, &child_status, 0);
    

}


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
	printf("AFTER FORK PROCRESSID = %d\n", getpid());
	if(pid == 0)
	{
	    if (!execve(choice.command[0], flags, newenvp))
	    {
		printf("FAILED\n");
	    }
	}
	else
	{
	    //if you don't want to run in the background we wait.
	    //wait for child to finish.
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
    create.isPipe = false;
    create.inputRedirect = false;
    create.outputRedirect = false;
    
    for(i = 0; i < BUFF_LEN; i++)
    {
	create.command[i] = malloc(20); // creates 20 max size of the string 
	//we need to free this later
    }
//    *(create.command[i]+1) = '\0';
	    
    return create;  

}

