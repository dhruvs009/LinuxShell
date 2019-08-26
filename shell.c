#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#define maxInput 1000
void takeInput(char *input){
    FILE *filePointer;
    printf(">>");
    fgets(input,maxInput,stdin);
    filePointer=fopen(".history","a+");
    fputs(input,filePointer);
    fclose(filePointer);
}

int parseCommand(char* input, char** parsedCommand){
    takeInput(input);
    int i;
    for(i=0; i<maxInput; i++){
        parsedCommand[i]=strsep(&input," ");
        if(parsedCommand[i]==NULL){
            break;
        }
    }
    int tempSize=strlen(parsedCommand[i-1]);
    parsedCommand[i-1][tempSize-1]='\0';
    return i;
}

void execCommand(char **parsedCommand, int size){  //needs all cases for particular commands else the program never reaches execInternalCommand or put execInternalCommand first. Take a look.
    int pid;
    int status=0;
    status=execInternalCommand(parsedCommand,size);
    if(status==-1){
        pid=fork();
        if(pid==0){
            status=execExternalCommand(parsedCommand,size);
            if(status==-1){
                printf("%s does not exist as a command. \n",parsedCommand[0]);
            }
            exit(0);
        }
        else{
            wait(NULL);
        }
    }
}

int execExternalCommand(char **parsedCommand, int size){
    return -1;
}

int execInternalCommand(char **parsedCommand, int size){
    int status=-1;
    if(strcmp(parsedCommand[0],"cd")==0){
        status=changeDirectory(parsedCommand,size);
    }
    else if(strcmp(parsedCommand[0],"echo")==0){
        status=echoX(parsedCommand,size);
    }
    else if(strcmp(parsedCommand[0],"pwd")==0){
        status=printPWD(size);
    }
    else if(strcmp(parsedCommand[0],"history")==0){
        status=printHistory(parsedCommand,size);
    }
    else{
        status=-1;
    }
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
            return 1;
        }
        else{
            return 0;
        }
    }
}

int echoX(char **parsedCommand, int size){    
    int count=0;
    int flag=0;
    char *temp;
    int i;
    int status=echoPrep(parsedCommand,size);
    if(status==0){
        i=1;
    }
    else if(status>=1 && status<=3){
        i=2;
    }
    else if(status==4){
        i=3;
    }
    if(status!=-1){
        for(;i<size; i++){
            if(status!=0 && status!=3){
                for(int j=0; j<strlen(parsedCommand[i]); j++){
                    if(parsedCommand[i][j]!='\\')
                        if(flag!=2){
                            printf("%c",(char)parsedCommand[i][j]);
                            count++;
                        }
                        else{
                            flag=0;
                        }
                    else if(j!=strlen(parsedCommand[i]-1)){
                        if(parsedCommand[i][j+1]=='a'){
                            printf("%c",'\a');
                        }
                        else if(parsedCommand[i][j+1]=='\\'){
                            printf("%c",'\\');
                        }
                        else if(parsedCommand[i][j+1]=='b'){
                            printf("%c",'\b');
                            count--;
                        }
                        else if(parsedCommand[i][j+1]=='c'){
                            flag=1;
                            break;
                        }
                        else if(parsedCommand[i][j+1]=='e'){
                            flag=2;
                        }
                        else if(parsedCommand[i][j+1]=='f'){
                            printf("%c",'\n');
                            for(int k=0; k<count; k++){
                                printf(" ");
                            }
                        }
                        else if(parsedCommand[i][j+1]=='n'){
                            printf("%c",'\n');
                        }
                        else if(parsedCommand[i][j+1]=='r'){
                            printf("%c",'\r');
                        }
                        else if(parsedCommand[i][j+1]=='t'){
                            printf("%c",'\t');
                        }
                        else if(parsedCommand[i][j+1]=='v'){
                            printf("%c",'\v');
                        }
                        else{
                            printf("%c%c",parsedCommand[i][j],parsedCommand[i][j+1]);
                        }
                        j++;
                    }
                    else{
                        if(flag!=2){
                            printf("%c",(char)parsedCommand[i][j]);
                            count++;
                        }
                        else{
                            flag=0;
                        }
                    }
                }
                if(flag!=2){
                    printf(" ");
                }
                if(flag==1){
                    break;
                }
            }
            else{
                printf("%s ",parsedCommand[i]);
            }
        }
        if(status<2){
            printf("%c",(char)'\n');
        }
    }
    return 0;
}

int echoPrep(char **parsedCommand, int size){
    int status=0;
    if(size>=2){
        if(strcmp(parsedCommand[1],"-e")==0){
            status=1;
        }
        else if(strcmp(parsedCommand[1],"-ne")==0 || strcmp(parsedCommand[1],"-en")==0){
            status=2;
        }
        else if(strcmp(parsedCommand[1],"-n")==0){
            status=3;
        }
        else if((strcmp(parsedCommand[1],"-e")==0 || strcmp(parsedCommand[1],"-n")==0) && (strcmp(parsedCommand[2],"-e")==0 || strcmp(parsedCommand[2],"-n")==0)){
            status=4;
        }
        return status;
    }
    else{
        return -1;
    }
}

int printHistory(char **parsedCommand, int size){
    if(size==1){
        FILE *filePointer;
        char dataFromFile[maxInput];
        filePointer=fopen(".history","r");
        int i=0;
        while(fgets(dataFromFile,maxInput,filePointer)!=NULL){
            i++;
            printf("%d. %s",i,dataFromFile);
        }
        fclose(filePointer);
        return 0;
    }
    else{
        printf("Too many arguments given.");
        return 3;
    }
}

int printPWD(int size){
    char direc[maxInput];
    getcwd(direc,maxInput);
    if(size<=2){
        printf("%s\n",direc);
    }
    return 0;
}