#include <signal.h>

#include "utilities.h"
#include "choice.h"

/*
 *launch
 *
 *Input: the user command.
 *Output: none
 *
 *This function handles stage piping if user inputs '|', and 
 *redirect if user inputs '<' or '>', else it runs the execve 
 *command normally. 
 *
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

    // this handles the piping command
    if(parsnip.isPipe == true)
    {
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
    //this handles I/O redirection
    else if(parsnip.inputRedirect || parsnip.outputRedirect)
    {
	redirect(parsnip);
    }
    else
    {
	execute(parsnip);
    }
    
}

/*
 *redirect
 *
 *Input: the struct for the command
 *Output: none. 
 *
 * This function change how I/O is handled depending on the structure passed 
 * in and executes the command. 
 *
*/
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
	    
	    // 0644 gives write access to the file. 
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

Input: the structure for the command
Output: none. 

This function calls fork and execve and creates the children processes
that run outside the parent. This runs the executable and terminantes the 
child process. 
*/

void execute(Choice choice)
{
    
	char *const newenvp[] = {NULL};
	int i;
	char *flags[choice.num_flags + 2]; 
	pid_t pid;
	int status;

	//ignores uninitialized elements in the command. 
	for(i = 0; i <= choice.num_flags; i++)
	{
	    flags[i] = choice.command[i];
	}

	flags[i] = NULL;

	pid = fork();

	if(pid == 0)
	{
	    if (!execve(choice.command[0], flags, newenvp))
	    {
		perror("error in execve\n");
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

Input: the uninitialized strucutre of the command
Output: the initialized structure

This is a helper function for the parsing function 
and allocates space for the strings. 

Limitation: does not free any of the allocated spaces. 

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
    }
	    
    return create;  

}

