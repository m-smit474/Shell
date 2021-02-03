#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void choice(char str[]);

int main( ) {

    char str[100];

    printf( "mySH$ ");       /* Command line prompt */
    scanf( "%s",str );       /* Read in command */

    while(strcmp(str, "exit") != 0)
    {
	choice(str);
	printf( "\nmySH$ ");       /* Command line prompt */
	scanf( "%s",str );       /* Read in command */
    }
    exit(0);
    
    //printf( "You entered: "); /* Echo command */
    //puts( str );

}

void choice(char str[])
{

    if(strcmp(str, "ls") == 0)
    {
	printf("inside ls");
    }
    else
    {
	printf("invalid entry");

    }

    //return;
}
	
 
