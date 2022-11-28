#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

void *isprime(void *x)
{
	int num = *((int *) x);
	int flag = 0;
	if(num==0 || num==1 || num==2)
	{
		return 1;
	}
	else
	{
		for(int i=2;i<num;i++)
		{
			if(num%i==0)
			{
				flag = 1;
			}
		}
	}
	if(!flag)
		return 1;
	else
		return 0;
}

void *ispalindrome(void *str)
{
	char *string = str;
	int cnt = 0;
	int flag = 0;
	for(int i=0;string[i]!='\0';i++)
		cnt++;

	for(int i=0;i<cnt/2;i++)
	{
		if(string[i] != string[cnt-i-1])
			flag = 1;
	}

	if(!flag)
		return 1;
	else
		return 0;
}

void *isangstorm(void *x)
{
	int num = (*(int *)x);
	int temp = num;
	int r = 0;
	int sum = 0;
	while(num>0)    
	{    
		r=num%10;    
		sum=sum+(r*r*r);    
		num=num/10;    
	}    
	
	if(temp==num)
		return 1;
	else
		return 0;
}

void *isperfect(void *x)
{
	int num = (*(int *)x);
	int sum = 0;
	
	for(int i=1;i<num;i++)
	{
		if(!(num%i))
			sum+=i;	
	}

	if(sum==num)
		return 1;
	else
		return 0;
}

int main()
{
	pthread_t thread_id_1,thread_id_2,thread_id_3,thread_id_4;
	int *prime;
	int pr;
	char string[50];
        int pal;

	printf("Enter number: ");
	scanf("%d",&pr);
	pthread_create(&thread_id_1, NULL, isprime,(void*)&pr);
	pthread_join(thread_id_1, (void *)&prime);
	printf("Result of Thread_%li: %d\n",thread_id_1,prime);


	printf("Enter String: ");
	scanf("%s",string);
	pthread_create(&thread_id_2, NULL, ispalindrome,(void*)&string);
        pthread_join(thread_id_2, (void *)&prime);
	printf("Result of Thread_%li: %d\n",thread_id_2,prime);
	

	printf("Enter Number: ");
        scanf("%d",&pr);
        pthread_create(&thread_id_3, NULL, isangstorm,(void*)&pr);
        pthread_join(thread_id_3, (void *)&prime);
        printf("Result of Thread_%li: %d\n",thread_id_3,prime);

	printf("Enter Number: ");
        scanf("%d",&pr);
        pthread_create(&thread_id_4, NULL, isperfect,(void*)&pr);
        pthread_join(thread_id_4, (void *)&prime);
        printf("Result of Thread_%li: %d\n",thread_id_4,prime);
	


	

	exit(0);
}
