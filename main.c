/*
   This shell program supports standard Linux commands (e.g., ls, pwd), as well as custom features
    that I added:
    - exec.c: contains code for executing linux commands such as ls, pwd, etc. 
    - date.c: prints the shell prompt in the format [dd/mm hh:mm] #
    - catch_signal.c: handles Ctrl + C to prevent the shell from exiting (when pressed, it simply ignores the signal)
    - change_dir.c: implements changing directory (cd) which is not a built in command in the exec family
    - redirect.c: provides input/output redirection to standard output

    The makefile makes an executable called customshell 
    so to run my shell in ubuntu simply call make and then run ./customshell
    and you should be able to start using the shell.

    Example use:

    [19/03 11:34] # ls
    Makefile  catch_signal.c  change_dir.c  customshell  date.c  exec.c  header.h  main.c  redirect.c
    [19/03 11:34] # 


    Example for redirecting stdout:
    [19/03 11:50] # ls > input.txt
    [19/03 11:51] # 

    You should see a new file called input.txt with contents of ls

*/
#include "header.h"

int main(void) {
    char* input = NULL;  
    size_t len = 0;      
    ssize_t read;
    //Assuming that your command line input wont reach over 150 arguments. I increased it becasue of cd ..      
    char* argv[150]; 

    //Call function in catch_signal.c to handle Ctrl + C
    signal(SIGINT, catch_sig);

    while (1) {
        //Call function in date.c to print the shell in the format [dd/mm hh:mm] #
        print_prompt();
        
        read = getline(&input, &len, stdin);

        if (read == -1) {
            //When ctrl + D is pressed exit the shell
            printf("logout\n");
            break;
        }

        //Remove the newline character at the end from getline()
        if (input[read - 1] == '\n') {
            input[read - 1] = '\0';
        }
        
        if (strchr(input, '>')) {
            //Call function in redirect.c for redirecting stdout
           redirect(input, argv);
        } else {
            //Call function in exec.c, split the arguments using strtok 
            split_input(input, argv);

            //Check if the first word is "cd"
            if (strcmp(argv[0], "cd") == 0) {
                //Call function in change_dir, execute the cd command
                change_dir(argv);
            } else {
                //Call function in exec.c, execute the command using execvp
                execute(argv);
            }
        }
    }
    //Free getline()
    free(input);
}
