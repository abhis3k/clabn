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
    printf("%d",key);

    int msgid = msgget(key, 0666|IPC_CREAT);
    printf("%d",msgid);

    message.msg_type=1;
    printf("Enter the message: ");
    fgets(message.msg_text,MAX,stdin);

    msgsnd(msgid,&message,sizeof(message),0);

    printf("Sent message: %s", message.msg_text);

    return 0;

}