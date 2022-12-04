#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
using namespace std;

int main(){

    key_t key;
    key = 4567;

    int shmid = shmget(key, 1024, 0666|IPC_CREAT);

    char *str = (char*) shmat(shmid,(void*)0,0);

    printf("Enter the date: ");
    gets(str);
    printf("\nSent data: %s",str);

    shmdt(str);

    return 0;

}