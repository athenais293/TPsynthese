#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "utils.h"

char *message = "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\n";
char *prompt = "enseash %\n";
char *command_error = "Erreur lors de l'exécution de la commande";

void displayWelcomeMessage(){
    write(STDOUT_FILENO,message,strlen(message));
}

void readCommand(char * console_buffer){
    write(STDOUT_FILENO,prompt,strlen(prompt));
    int byte_read=read(STDIN_FILENO,console_buffer,strlen(console_buffer));
    console_buffer[byte_read-1]=0;
}

void executeCommand(char *command){
    int pid=fork();
    if (pid==0){
        execlp(command,command,NULL);
        write(STDOUT_FILENO,command_error,strlen(command_error));
        exit(EXIT_FAILURE);;
    }else if (pid > 0) {
        wait(NULL);
    }
}