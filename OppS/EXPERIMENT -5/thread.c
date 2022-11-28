#include<unistd.h>
#include<pthread.h>

void *myThreadFun()
{
	sleep(1);
	printf("\nArun is genius\n");
	return NULL;
}
int main()
{
	pthread_t thread_id;
	printf("before thread\n");
	pthread_create(&thread_id,NULL,myThreadFun,NULL);
	pthread_join(thread_id,NULL);
	printf("\nAfter Thread\n");
	exit(0);
}
