#include "header.h"

//Function that redirects stdout to a file 
void redirect(char* input, char* argv[]) {
    //Split the input at the '>' symbol
    strtok(input, ">");  
    //Everything before '>' is the command like ls, pwd 
    char* command = input;  

    //Get the filename which is after '>', we only care about the first word after '>' 
    //ignoring everything after thats why we don't need a loop this time
    char* file_name = strtok(NULL, " "); 

    if (file_name == NULL) {
        perror("syntax error, didn't input file name");
        return;
    }

    // Open the file for writing and reading, create the file if it doesn't exist, truncate if it does
    int file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file == -1) {
        perror("Error opening file");
        return;
    }

    //Create a child process
    pid_t pid = fork(); 

    if (pid == -1) {
        perror("Failed to create child process");
        close(file);
        return;
    }
    //Child process
    if (pid == 0) {  
        //Replace the file descriptor in stdout (1), to the file so stdout now redirects to the file
        if (dup2(file, 1) == -1) {
            perror("Error in dup2 failed to change file descriptor");
            close(file);
            exit(EXIT_FAILURE); 
        }

        //Split the command parts into arguments
        char* token = strtok(command, " ");
        int i = 0;
        //Iterate through the tokens until there are no tokens left.
        while (token != NULL) {
            //Store the current token in the argv array.
            argv[i++] = token;
            //Moves to the next token
            token = strtok(NULL, " ");
        }
        //argv's last element needs to be null, e.g. argv[] = {"ls", "-l", NULL}
        argv[i] = NULL; 

        //Execute the command 
        if (execvp(argv[0], argv) == -1) {  
            //If execvp fails print error and exit child process
            perror("execvp failed");  
            exit(EXIT_FAILURE); 
        }
        close(file); 
    } else {  
        // Parent process 
        wait(NULL);  
    }
}
