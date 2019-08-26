#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#define maxInput 1000
int main(){
    char input[maxInput];
    char *parsedCommand[maxInput];
    int x;
    while(1){
        x=parseCommand(input,parsedCommand);
        if(x==1 && strcmp(parsedCommand[0],"exit")==0){
            break;
        }
        execCommand(parsedCommand,x);
    }
    return 0;
}