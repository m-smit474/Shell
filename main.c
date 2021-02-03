#include <stdio.h>
#include <string.h>

int main( ) {

    char str[100];

    printf( "mySH$ ");       /* Command line prompt */
    scanf( "%s",str );       /* Read in command */
    
    printf( "You entered: "); /* Echo command */
    puts( str );

    return 0;
}
