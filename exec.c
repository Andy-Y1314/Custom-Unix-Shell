#include "header.h"

//Function that splits input in command line into individual tokens
void split_input(char* input, char* argv[]) {
    //Split the input string into individual tokens
    char* token = strtok(input, " ");
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
}

//Function that creates a new child process and then execute command, like ls, pwd
void execute(char* argv[]) {

    //Creates a new child process
    pid_t pid = fork();  

    if (pid == - 1) {  
        perror("Failed to create child process");
        return;
    }

    //Child process
    if (pid == 0) { 
        //Execute the command stored in argv[0]
        if (execvp(argv[0], argv) == -1) {  
            //If command doesn't execute print error
            perror("Unknown command");
             //Professor recommended to use full symbol instead of just number, could also just use exit(1)
            exit(EXIT_FAILURE);
        } 
    } else {  
       // Parent proccess wait until child terminates to avoid zombie state
       wait(NULL);
    }
}