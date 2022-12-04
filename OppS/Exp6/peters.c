#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>
int i=0,j=1,flag[2];
int count,loop;
int turn=0;
void *P1(void *vargp)
{
do
{
flag[i]=1;
turn=j;
count++;
loop++;
while(flag[j]==1&&turn==j);
printf("\nCritical section of P1, count=%d, loop=%d",count,loop);
flag[i]=0;
printf("\nRemainder section of P1");
}while(1&&loop<=10);
}
void *P2(void *vargp)
{
do
{
flag[j]=1;
turn=i;
count--;
loop++;
while(flag[i]==1&&turn==i);
printf("\nCritical section of P2, count=%d, loop=%d",count,loop);
flag[j]=0;
printf("\nRemainder section of P2");
}while(1&&loop<=20);
}

int main()
{
pthread_t P1_t,P2_t;
pthread_create(&P1_t,NULL,P1,(void *) &P1_t);
//sleep(10);
pthread_create(&P2_t,NULL,P2,(void *) &P2_t);
//sleep(10);
pthread_join(P1_t,NULL);
pthread_join(P2_t,NULL);
exit(1);
return 0;
}
