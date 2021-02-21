#include <fcntl.h>
#include <stdlib.h>

#include "utilities.h"
#include "choice.h"
#include <stdio.h>

int main()
{

    char command_line[BUFF_LEN + 1];
    Choice process;

//    printf("HERE = %s\n",*process.command);
    
    read_write(command_line);
    process = parsing(command_line); //process the user input

//    printf("MAIN PROCESS = %s\n", *process.command);
    while(compare_strings(command_line, "exit\n") != 0)
    {
	//choice(command); /*delete this with new func*/
	execute(process);
	read_write(command_line);
	//process the user input
	process = parsing(command_line);
    }

    exit(0);
   
}


	
 
