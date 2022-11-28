#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define SHMsz 27
int main(void)
{
	char c;
	int shmid;
	key_t key;
	char *shm,*s;
	key = 1234;
	printf("sender program");
	if((shmid = shmget(key,SHMsz,IPC_CREAT|0666))<0)
	{
		perror("Error");
		exit(1);
	}
	if((shm = shmat(shmid,NULL,0))==(char *)-1)
	{
		perror("shmat");
		exit(1);
	}
	s=shm;
	for(c='a';c<='z';c++)
	{
		*s++=c;
	}
	*s='\0';
	while(*shm!='#')
	{
		sleep(10);
		printf("Process not completed yet");
	}
	printf("Process completed.");
	return 0;
}
