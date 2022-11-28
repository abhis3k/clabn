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
        while(1)
        {
        	printf("\nWaiting for msg from sender\n");
        	if(msgrcv(mqid,&txt,sizeof(txt),0,0)==-1)
        	{
        		perror("msgrcv");
        	}	
        	printf("\nMsg received is %s\n",txt);
        	if(strcmp(txt,"bye")==0)
        	{
        		break;
        	}
        }
        printf("\nEnd from receiver\n");
        return 0;
}
