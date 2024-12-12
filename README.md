# TP synthèse
## Ensea in the Shell
### The aim of this practical project is to create a microshell, i.e. a command-line interface for executing system commands.


Q1. Display a welcome message and a simple prompt  
I created a function that displays a messsage and then call this function in my main.

Q2. Execution of the entered command and return to the prompt  
I created two functions, one to read the entered commande and the other one to execute this command. And I use my previous function displayMessage in order to display the prompt. The readCommand function reads the command entered and removes the last character corresponding to the backspace. The executeCommand function creates a child process with the fork function, which allows the shell to execute each command in a separate process, ensuring its smooth operation while isolating command errors and signals. Then execlp execute the command.

Q3. Management of the shell output with the command ”exit”  
Our code is working :  
![Microshell](microshell.PNG)
