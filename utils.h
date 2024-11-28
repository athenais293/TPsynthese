#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void displayWelcomeMessage();
void readCommand(char *console_buffer);
void executeCommand(char *command);

#endif