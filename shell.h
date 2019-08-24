#ifndef SHELL_H
#define SHELL_H
void takeInput(char *input);
int parseCommand(char *input, char **parsedCommand);
void execCommand(char **parsedCommand, int size);
int execInternalCommand(char **parsedCommand, int size);
void changeDirectory(char **parsedCommand, int size);
#endif