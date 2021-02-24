#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "utilities.h"
#include "choice.h"

const char *prompt_line = "mySH$ ";
int write_bytes, read_bytes;
/*
Parsing
Input: The command line that has been preprocessed by the readwrite function
Output: An array list with the first element being the command and remaining eleme\
nts being the flags
The main for loop cycles through each character until the end of the input,
the key part in this function is line *(parsnip.command[k] + j) = userInput[i]
which sends either the command or the flag into the array.
*/

Choice parsing(char userInput[], int *i)
{
//    int i;
    int j;
    int k;
    Choice parsnip;
    char temp[BUFF_LEN + 1];
    bool isWord;


    parsnip = new_choice(parsnip);


    for (k = 0; *i < BUFF_LEN && userInput[*i] != '\0' && userInput[*i] != \
	     '\n' && userInput[*i] != '|' ; (*i)++)
    {
	isWord = false;


	while (userInput[*i] == ' ')
	{
	    (*i)++;
	}

	if(userInput[*i] == '&')
	{
	    parsnip.runInBackground = true;
	    (*i)++;
	}

	
	j = 0;

	while(userInput[*i] != '\n' && userInput[*i] != ' ')
	{
	    isWord = true;
	    *(parsnip.command[k] + j) = userInput[*i];
	    j++;
	    (*i)++;
	}

	if(isWord)
	    k++;
    }

    if(userInput[*i] == '|')
    {
	parsnip.isPipe = true;
	(*i)++;
    }

    parsnip.num_flags = k - 1;

    return parsnip;
}



void read_write(char command[BUFF_LEN])
{
   
    write_bytes = write(WRITE, prompt_line, 6); /*prints out shell prompt*/

    read_bytes = read(READ, command, BUFF_LEN); /*reads command from user*/

    if(read_bytes < BUFF_LEN)                   /*clears buffer */
    {
	command[read_bytes] = '\0';
//	printf("READ_WRITE COMMAND = %s\n", command);

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


