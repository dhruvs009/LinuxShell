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
        exit(0);
    }
    else{
        wait(NULL);
    }
    if(status==-1){
        status=execInternalCommand(parsedCommand,size);
    }
    if(status==-1){
        printf("%s does not exist as a command. \n",parsedCommand[0]);
    }
}

int execInternalCommand(char **parsedCommand, int size){
    int status=0;
    if(strcmp(parsedCommand[0],"cd")==0){
        status=changeDirectory(parsedCommand,size);
    }
    else if(strcmp(parsedCommand,"echo"))
    return status;
}

int changeDirectory(char **parsedCommand, int size){
    if(size>2){
        printf("Too many directories given at once.\n");
        return 1;
    }
    else if(size==1){
        printf("Insufficient arguments. Please give a directory to move to.\n");
        return 1;
    }
    else{
        if(chdir(parsedCommand[1])!=0){
            printf("No such directory as %s\n",parsedCommand[1]);
        }
        return 0;
    }
}