
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

int main()
{
	key_t key;
	int msgid;

	
	key = ftok("progfile", 65);

	
	msgid = msgget(key, 0666 | IPC_CREAT);

	
	msgrcv(msgid, &message, sizeof(message), 1, 0);
	int arr[100],k=0;
	
	for(int i=0;message.mesg_text[i]!='\0';++i){
		if(message.mesg_text[i]!=' '){
			arr[k++] = (message.mesg_text[i] - '0');
		}
	}
	
	for(int i=0;i<k;i++)
	{
		printf("%d",arr[i]);
	}

	printf("Data Received is : %s \n",
					message.mesg_text);

	
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}

