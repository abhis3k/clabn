#include<stdio.h>
#include<pthread.h>
//#include"mythreads.h"

int flag[2], turn, max = 1e5, ans = 0;

void lock_init(){
    flag[0]=flag[1]=0;
    turn=0;
}

void lock(int self){
    flag[self]=1;
    turn=1-self;

    while(flag[1-self]==1 && turn==1-self);
}

void unlock(int self){
    flag[self]=0;
}

void fun(void* s){
    int id = (int *)s;
    printf("Thread ID: %d\n",s);

    lock(id);

    for(int i=0; i<max; i++){
        ans++;
    }

    unlock(id);
}

int main(){
    pthread_t p1, p2;

    pthread_create(&p1,NULL,fun,(void *)0);
    pthread_create(&p2,NULL,fun,(void *)1);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    printf("\nValue of ans: %d",ans);

    return 0;
}