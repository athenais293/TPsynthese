#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

#define MAX_COMMAND_LENGTH 128

int main (){
    char console_buffer [MAX_COMMAND_LENGTH];
    displayWelcomeMessage();

    while(1){
        readCommand(console_buffer);
        executeCommand(console_buffer);
    }
}


