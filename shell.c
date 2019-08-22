#include <stdio.h>
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
    return i;
}

int main(){
    char input[maxInput];
    char *parsedCommand[maxInput];
    int x;
    while(1){
        x=parseCommand(input,parsedCommand);
        for(int i=0; i<x; i++){
            printf("%s\n",parsedCommand[i]);
        }
        if(x==1 && strcmp(parsedCommand[0],"exit\n")==0){
            break;
        }
        execMyCommand(parsedCommand);
    }
    return 0;
}