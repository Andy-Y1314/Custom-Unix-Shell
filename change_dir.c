#include "header.h"

//Function for the cd command
void change_dir(char* argv[]) {
    //Check for directory given after cd if empty default to HOME
    if (argv[1] == NULL) {
        char* path = getenv("HOME");
       
        //Change directory to "HOME", if not successful throw error
        if (chdir(path) != 0) {
            perror("cd to HOME failed");
        }
    } else {
        //Change directory to the one after cd in argv[]
        if (chdir(argv[1]) != 0) {
            fprintf(stderr, "cd: %s: ", argv[1]);
            perror("");
        }
    }
}