#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#define N 5

#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
sem_t stLock,pLock[N];
int state[N];
void *philosopher(void*);
void put_forks(int );
void take_forks(int );
void test(int );
void *philosopher(void* p)
{
	int i,j;
	i=*(int*)p;
	//for(j=0;j<5;j++)
	// printf("\nBefore Taking Forks (%d): P-%d: %d",i,j,state[j]);
	take_forks(i);
	for(j=0;j<5;j++)
		printf("\nDuring Eating (%d): P-%d: %d",i,j,state[j]);
	printf("\n\nP-%d is EATING now...\n",i);
	for(j=0;j<1000000000;j++);
	put_forks(i);
	for(j=0;j<5;j++)
		printf("\nAfter Putting Fork Down (%d): P-%d: %d ",i,j,state[j]);
}
void take_forks(int i)
{
	sem_wait(&stLock);
	state[i]=HUNGRY;
	test(i);
	sem_post(&stLock);
	sem_wait(&pLock[i]);
}
void put_forks(int i)
{
	sem_wait(&stLock);
	state[i]=THINKING;
	test(LEFT);
	test(RIGHT);
	sem_post(&stLock);	
}
void test(int i)
{
	if(state[i]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
	{
		state[i]=EATING;
		sem_post(&pLock[i]);
	}
}
void main()
{
	int i,a[5]={0,1,2,3,4},j;
	pthread_t p[5];
	sem_init(&stLock,0,1);
	for(j=0;j<N;j++)
		sem_init(&pLock[j],0,0);
	for(i=0;i<5;i++)
		pthread_create(&p[i],NULL,philosopher,&a[i]);
	for(i=0;i<5;i++)
		pthread_join(p[i],NULL);
}

