#include <fcntl.h>
#include <stdlib.h>

#include "utilities.h"
#include "choice.h"

int main()
{

    char command[BUFF_LEN];

    read_write(command);
    //process the user input 
    
    while(compare_strings(command, "exit\n") != 0)
    {
	choice(command); /*delete this with new func*/
	read_write(command);
	//process the user input
    }

    exit(0);

    
    return 0;
}


	
 
