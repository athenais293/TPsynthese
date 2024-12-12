#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

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

void readCommand(char *console_buffer, char *dynamic_prompt) {
    displayMessage(dynamic_prompt);
    ssize_t byte_read = read(STDIN_FILENO, console_buffer, MAX_COMMAND_LENGTH - 1);
    if (byte_read > 0) {
        console_buffer[byte_read - 1] = '\0'; //Replaces the last character (carriage return) with a null character
    } else {
        console_buffer[0] = '\0'; 
    }
}

int executionTime(struct timespec start_time, struct timespec end_time){
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long nanoseconds = end_time.tv_nsec - start_time.tv_nsec;
    return (int) ((seconds + nanoseconds * 1e-9) * 1000); 
}

void executeCommand(char *command, char *dynamic_prompt) {
    struct timespec start_time, end_time;
    pid_t pid=fork(); //creation ofa child process to deal with the command

    clock_gettime(CLOCK_REALTIME, &start_time);

    if (pid==0){ 
        //child process
        //execlp(command,command,NULL);

        char *args[MAX_COMMAND_LENGTH];
        char *token = strtok(command, " ");  //to split the command when there is a space
        int i = 0;

        while (token != NULL) { //split until all arguments have been dealt
            args[i] = token;
            token = strtok(NULL, " "); 
            i++;
        }
        args[i] = NULL; 

        execvp(args[0], args);
        displayMessage(COMMAND_ERROR);
        exit(EXIT_FAILURE);;
    }
    else if (pid > 0) //parent process
    {
        int status;
        waitpid(pid, &status, 0);//has to wait for the child to finish

        clock_gettime(CLOCK_REALTIME, &end_time);

        int duration_ms = executionTime(start_time, end_time);

        if (WIFEXITED(status)) {
            snprintf(dynamic_prompt, MAX_COMMAND_LENGTH, "enseash [exit:%d|%dms] %% ", WEXITSTATUS(status), duration_ms);
        } else if (WIFSIGNALED(status)) {
            snprintf(dynamic_prompt, MAX_COMMAND_LENGTH, "enseash [sign:%d|%dms] %% ", WTERMSIG(status), duration_ms);
        }
        
    }
    else {
        displayMessage(PROCESS_ERROR);
    }
}

int main() {
    char console_buffer[MAX_COMMAND_LENGTH];
    char dynamic_prompt[MAX_COMMAND_LENGTH] = PROMPT;
    displayMessage(WELCOME_MESSAGE);

    while (1) {
        readCommand(console_buffer, dynamic_prompt);

        if (strcmp(console_buffer, EXIT) == 0) {
            displayMessage(GOODBYE);
            break;
        }

        if (strlen(console_buffer) > 0) {
            executeCommand(console_buffer, dynamic_prompt);
        }
    }

    return 0;
}


