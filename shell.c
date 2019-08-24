#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#define maxInput 1000
void takeInput(char *input){
    printf(">>");
    fgets(input,maxInput,stdin);
}

int parseCommand(char* input, char** parsedCommand)
{
    takeInput(input);
    int i;
    for(i=0; i<maxInput; i++){
        parsedCommand[i]=strsep(&input, " ");
        if(parsedCommand[i]==NULL){
            break;
        }
    }
    int tempSize=strlen(parsedCommand[i-1]);
    parsedCommand[i-1][tempSize-1]='\0';
    return i;
}

void execCommand(char **parsedCommand, int size){
    int pid;
    int status;
    pid=fork();
    if(pid==0){
        status=execvp(parsedCommand[0],parsedCommand);
        if(status==-1){
            execInternalCommand(parsedCommand,size);
        }
        exit(0);
    }
    else{
        wait(NULL);
    }
}

void execInternalCommand(char **parsedCommand, int size){
    
}