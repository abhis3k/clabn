#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void MyFunc1()
{
	printf("\nNIT Trichy\n");
	sleep(2);
}
void MyFunc2()
{
	printf("\nSASTRA deemed University\n");
	sleep(2);
}
void MyFunc3()
{
	printf("\nSRM trichy\n");
	sleep(2);
}
void MyFunc4()
{
	printf("\nISRO\n");
	sleep(2);
}
int main()
{
	pthread_t thread1,thread2,thread3,thread4;
	pthread_create(&thread1,NULL,MyFunc1,NULL);
	pthread_create(&thread2,NULL,MyFunc2,NULL);
	pthread_create(&thread3,NULL,MyFunc3,NULL);
	pthread_create(&thread4,NULL,MyFunc4,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	pthread_join(thread4,NULL);
	exit(0);
}
