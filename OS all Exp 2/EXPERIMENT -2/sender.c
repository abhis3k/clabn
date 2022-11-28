#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
int main(void)
{
        int mqid;int len;
        key_t key;char txt[100];
        key = 1234;
        if((mqid=msgget(key,IPC_CREAT|0666))==-1)
        {
                perror("msgget");
                exit(1);
        }
        printf("Msg queue created\n");
        while(1)
        {
                printf("\nEnter Msg\n");
                gets(txt);
                len = strlen(txt);
                if(msgsnd(mqid,&txt,len,0)==-1)
                {
                        perror("msgsnd");
                        exit(1);
                }
                if(strcmp(txt,"bye")==0)
                {
                        break;
                }
        }
        printf("\nEnd from Sender\n");
        return 0;
}
