#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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



int main(){
    char input[maxInput];
    char *parsedCommand[maxInput];
    int x;
    while(1){
        x=parseCommand(input,parsedCommand);
        // for(int i=0; i<x; i++){
        //     printf("%s",parsedCommand[i]);
        // }
        if(x==1 && strcmp(parsedCommand[0],"exit")==0){
            break;
        }
        execCommand(parsedCommand,x);
    }
    return 0;
}