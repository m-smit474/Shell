#include <fcntl.h>

#include "utilities.h"
#include "choice.h"

int main()
{


    read_write();

    while(compare_Strings(command, "exit\n") != 0)
    {
	choice(command); /*change this*/
	read_write();
    }

    exit(0);
=======

    prompt();
    
    return 0;
}


	
 
