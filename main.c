#include <fcntl.h>
#include <stdlib.h>

#include "utilities.h"
#include "choice.h"
#include <stdio.h>

int main()
{

    char command_line[BUFF_LEN + 1];
    Choice process;

    read_write(command_line);

    //initiates the process of creating the shell and executing the command line entry. 
    while(compare_strings(command_line, "exit\n") != 0)
    {
	launch(command_line);
	read_write(command_line);
    }

    exit(0);
   
}


	
 
