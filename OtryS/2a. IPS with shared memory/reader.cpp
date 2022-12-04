#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
using namespace std;

int main(){

    key_t key = ftok("shmfile",65);

    int shmid = shmget(key, 1024, 1066|IPC_CREAT);

    char *str = (char*) shmat(shmid,(void*)0,0);

    printf("Received message: %s", str);

    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;

}