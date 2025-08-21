#include "header.h"

//Prints the shell prompt # with the date first, in the format [dd/mm hh:mm] #
void print_prompt() {
    //Get the current time
    time_t t = time(NULL);  
    struct tm date = *localtime(&t);  
    
    //Print the time in the format [dd/mm hh:mm] #
    printf("[%02d/%02d %02d:%02d] # ", date.tm_mday, date.tm_mon + 1, date.tm_hour, date.tm_min);
    
}
