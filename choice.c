#include <stdio.h>
#include <unistd.h>
#include <string.h> // Need to remove at some point

#include "choice.h"

void execute(Choice choice)
{
    char *path = "/usr/bin/";
    strcat(path,choice.command);
    
    char *const newargv[] = { path, NULL };
    char *const newenvp[] = { NULL };

    if(!execve( path, newargv, newenvp))
    {
	// Failed to execute
    }

    // Does not reach
}
