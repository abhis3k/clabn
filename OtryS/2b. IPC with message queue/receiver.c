#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10

struct msg_queue{
    long msg_type;
    char msg_text[100];
}message;

int main(){

    key_t key;
    key = 1235;

    int msgid = msgget(key, 0666|IPC_CREAT);

    msgrcv(msgid,&message,sizeof(message),0,0);

    printf("Received message: %s",message.msg_text);

    msgctl(msgid,IPC_RMID,NULL);

    return 0;

}