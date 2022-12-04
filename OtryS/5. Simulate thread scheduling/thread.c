#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void mythread1(){
    printf("hellllo 1");
    sleep(2);
}

void mythread2(){
    printf("hellllo 2");
    sleep(2);
}

void mythread3(void *arg){
    int *arg1 = (int *)arg;
    printf(arg1);
    sleep(2);
}

int main(){
    pthread_t thread1, thread2, thread3;
    int a = 2;

    pthread_create(&thread1,NULL,mythread1,NULL);
    pthread_create(&thread2,NULL,mythread2,NULL);
    pthread_create(&thread3,NULL,mythread3,(void *)&a);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    exit(0); //important
}