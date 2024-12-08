#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 128
#define WELCOME_MESSAGE  "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n"
#define PROMPT "enseash % "
#define COMMAND_ERROR "Erreur lors de l'exécution de la commande.\n"
#define PROCESS_ERROR "Erreur lors de la création du processus"
#define EXIT "exit"
#define GOODBYE "Bye bye ...\n"

void displayMessage(char *message){
    write(STDOUT_FILENO,message,strlen(message));
}

void readCommand(char *console_buffer) {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    int byte_read = read(STDIN_FILENO, console_buffer, MAX_COMMAND_LENGTH - 1);
    if (byte_read > 0) {
        console_buffer[byte_read - 1] = '\0'; 
    } else {
        console_buffer[0] = '\0'; 
    }
}

void executeCommand(char *command){
    pid_t pid=fork();

    if (pid==0){
        execlp(command,command,NULL);
        displayMessage(COMMAND_ERROR);
        exit(EXIT_FAILURE);;
    }
    else if (pid > 0) 
    {
        wait(NULL);
    }
    else {
        displayMessage(PROCESS_ERROR);
    }
}

int main() {
    char console_buffer[MAX_COMMAND_LENGTH];
    displayMessage(WELCOME_MESSAGE);

    while (1) {
        readCommand(console_buffer);

        if (strcmp(console_buffer, EXIT) == 0) {
            displayMessage(GOODBYE);
            break;
        }

        if (strlen(console_buffer) > 0) {
            executeCommand(console_buffer);
        }
    }

    return 0;
}


