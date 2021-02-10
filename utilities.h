#ifndef UTILITIES_H
#define UTILITIES_H

#define WRITE 1
#define READ 0
#define BUFF_LEN 256



void read_write(char command[BUFF_LEN]);
int compare_strings(const char *string1, const char *string2);
void choice(char command[]);



#endif 
