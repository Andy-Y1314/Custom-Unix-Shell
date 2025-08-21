#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>

//Function that splits input in command line into individual tokens
void split_input(char* input, char* args[]);
//Function that creates a new child process and then execute command, like ls, pwd
void execute(char *args[]);

//Prints the shell prompt # with the date first, in the format [dd/mm hh:mm] #
void print_prompt();

//Function to allow program to continue and not pause if user types ctrl + c
void catch_sig();

//Function for the cd command
void change_dir(char* argv[]);

//Function that redirects stdout to a file 
void redirect(char *input, char *argv[]);