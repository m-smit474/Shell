#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"
#include "choice.h"

const char *prompt_line = "mySH$ ";
int write_bytes, read_bytes;

/*
 *Parsing
 *
 *Input: The command line that has been preprocessed by the readwrite function
 *Output: A structure containing the whole user command line. 
 *
 *The main for loop cycles through each character until the end of the input,
 *the key part in this function is line *(parsnip.command[k] + j) = userInput[i]
 *which sends either the command or the flag into the array.
 *
*/

Choice parsing(char userInput[], int *i)
{

    int j,k,l;
    Choice parsnip;
    char temp[BUFF_LEN + 1];
    bool isWord;

    parsnip = new_choice(parsnip);

    /*this loop goes through each character of the user input, and if it hits a special character
      the loop will stop.*/
    for (k = 0; *i < BUFF_LEN && userInput[*i] != '\0' && userInput[*i] != \
	     '\n' && userInput[*i] != '|' && userInput[*i] != '>' && userInput[*i] != '<'; (*i)++)
    {
	isWord = false;

	//ignores all whitespaces in the input. 
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

	// this loop copies the command into the structure. 
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
    else if(userInput[*i] == '<' || userInput[*i] == '>')
    {

	if(userInput[*i] == '>') 
	{
	    parsnip.outputRedirect = true;
	}
	else
	{
	    parsnip.inputRedirect = true;
	}
	
	(*i)++;
	
	while(userInput[*i] == ' ')
	{
	    (*i)++;
	}
	
	for(l = 0; l < FILE_LEN && userInput[*i] != '\n' && userInput[*i] != ' ' ; l++, (*i)++)
	{

	    parsnip.fileName[l] = userInput[*i];

	}
	
	
    }
    parsnip.num_flags = k - 1;

    return parsnip;
}

/*
 * prompt
 *
 * Input: character array. 
 *
 * Output: The command line stored in the character array.  
 *
 * This function outputs the prompt line 'mySH$' and reads in the 
 * user input. Using system calls.  
 *
*/

void prompt(char command[BUFF_LEN])
{
   
    write_bytes = write(WRITE, prompt_line, 6); /*prints out shell prompt*/

    read_bytes = read(READ, command, BUFF_LEN); /*reads command from user*/

    if(read_bytes < BUFF_LEN)                   /*clears buffer */
    {
	command[read_bytes] = '\0';

    }

}

/*
 * compare_strings
 *
 *Input: The two string characters being compared. 
 *
 *Output: Depending if the strings match either a 0 if they match
 * or a negative number if they do not. 
 *
 * Compares two strings. 
 *
 */

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





