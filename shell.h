#ifndef SHELL_H
#define SHELL_H
void takeInput(char *input);
int parseCommand(char *input, char **parsedCommand);
void execCommand(char **parsedCommand, int size);
int execExternalCommand(char **parsedCommand, int size);
int execInternalCommand(char **parsedCommand, int size);
int changeDirectory(char **parsedCommand, int size);
int echoX(char **parsedCommand, int size);
int echoPrep(char **parsedCommand, int size);
int printHistory(char **parsedCommand, int size);
int printPWD(int size);
#endif