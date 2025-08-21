#include "header.h"

//Function to allow program to continue and not pause if user types ctrl + c
void catch_sig() {
    printf("\n");
    print_prompt();
    //Clear the output buffer
    fflush(stdout);  
}