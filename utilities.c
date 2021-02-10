#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>


#include "utilities.h"


const char *prompt_line = "mySH$ ";
int write_bytes, read_bytes;

void read_write(char command[BUFF_LEN])
{
   
    write_bytes = write(WRITE, prompt_line, 6); /*prints out shell prompt*/

    read_bytes = read(READ, command, BUFF_LEN); /*reads command from user*/

    if(read_bytes < BUFF_LEN)                   /*clears buffer */
    {
	command[read_bytes] = '\0';
//	printf("%s\n", command);

    }

}

//create strcat func here

int compare_strings(const char *string1, const char *string2)
{
    int result;

    while(*string1)
    {
	if(*string1 != *string2)
	    break;

	string1++;
	string2++;
    }

    return *(const unsigned char*)string1 - *(const unsigned char*)string2; 
}


void choice(char command[])
{

    if(compare_strings(command, "ls\n") == 0)
    {
	printf("inside ls\n");
    }
    else
    {
	printf("invalid entry\n");
    }
    
}


