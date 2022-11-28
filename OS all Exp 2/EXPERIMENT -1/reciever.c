#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define SHMsz 27
int main(void)
{	
	int shmid;
	key_t key;
	char *shm,*s;
	key = 1234;
	printf("Reciever program");
	if((shmid=shmget(key,SHMsz,0666))<0)
	{
		perror("Error");
		exit(1);
	}
	if((shm = shmat(shmid,NULL,0))==(char*)-1)
	{
		perror("shmat");
		exit(1);
	}
	for(s=shm;*s!=' ';s++)
	{
		putchar(*s);
	}
	printf("\n");
	*shm='#';
}
