#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void MyFunc1()
{
	printf("\nNIT Trichy\n");
	sleep(2);
}
 
int main()
{
	pthread_t threads[3];
	for(int i=0;i<=3;i++)
	{
		printf("%Id",threads[i]);
		pthread_create(&threads[i],NULL,MyFunc1,(void *)&threads[i]);
	}
	for(int i=0;i<=3;i++)
	{
		pthread_join(threads[i],NULL);
	}
	exit(0);
}
