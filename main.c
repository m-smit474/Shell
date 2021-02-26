#include <fcntl.h>
#include <stdlib.h>

#include "utilities.h"
#include "choice.h"
#include <stdio.h>

/*
 *
 *This program initiates the process of creating the shell and executing the 
 *command line entry. The command executes once the user hits enter. 
 *This supports background jobs, single stage piping, and basic I/O redirection. 
 *
 *Known bugs: 
 * Sometimes when user enters 'exit' the program will sometimes
 * not close. User has to enter 'exit' multiple times (we think it's a 
 * race condition). 
 *
 *Limitations: 
 * User has to enter full path for the executable they want to run. 
 *
*/

int main()
{

    char command_line[BUFF_LEN + 1];
    Choice process;

    prompt(command_line); 

    
    while(compare_strings(command_line, "exit\n") != 0)
    {
	launch(command_line);
	prompt(command_line);
    }

    exit(0);
   
}


	
 
