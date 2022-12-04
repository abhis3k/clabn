#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){

    int inP[2], outP[2]; //Input and Output pipe
    pid_t pID;

    char fixed_str[]="Itsnottheendd";
    char input_str[100];

    if(pipe(inP)==-1){
        printf("In-pipe failed");
        return 1;
    }

    if(pipe(outP)==-1){
        printf("Out-pipe failed");
        return 1;
    }

    printf("Enter input string: ");
    scanf("%s",input_str);
    pID = fork();

    if(pID < 0){
        printf("\nFork failed");
        return 1;
    }

    //parent process
    else if(pID > 0){
        char concat_str[100];

        close(inP[0]); //closing the reading end of in pipe

        write(inP[1],input_str,strlen(input_str)+1); //sending the input str with write end of in pipe

        close(inP[1]);

        wait(NULL); //waitign for child process

        close(outP[1]); //closing write end of out pipe

        read(outP[0],concat_str,100);

        printf("Concat String: %s\n", concat_str);

        close(outP[0]);
    }

    //child process
    else{
        close(inP[1]);

        char concat_str[100];

        read(inP[0],concat_str,100);

        int l = strlen(fixed_str);
        for(int i=0; i<strlen(fixed_str); i++){
            concat_str[l++] = fixed_str[i];
        }

        close(inP[0]);

        close(outP[0]);

        write(outP[1],concat_str,strlen(concat_str)+1);

        close(outP[1]);

        exit (0);
    }

}