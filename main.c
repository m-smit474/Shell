#include <fcntl.h>
#include <stdlib.h>

#include "utilities.h"
#include "choice.h"

int main()
{

    char command[BUFF_LEN];
    Choice process;
    read_write(command);
    //process the user input
    process = parsing(command);
    
    while(compare_strings(command, "exit\n") != 0)
    {
	//choice(command); /*delete this with new func*/
	execute(process);
	read_write(command);
	//process the user input
	process = parsing(command);
    }

    exit(0);

    
    return 0;
}


	
 
