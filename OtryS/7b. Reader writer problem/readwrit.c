#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

sem_t sem;
pthread_mutex_t mutex;
int cnt=1;
int readcount=0;

void *writer(void *w){
    sem_wait(&sem);
    cnt = cnt*2;
    printf("Writer %d wrote cnt to %d\n", (*((int *)w)), cnt);
    sem_post(&sem);
}

void *reader(void *r){
    pthread_mutex_lock(&mutex);
    readcount++;
    if(readcount==1){
        sem_wait(&sem);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d reads cnt as %d\n", (*((int *)r)), cnt);

    pthread_mutex_lock(&mutex);
    readcount--;
    if(readcount==0){
        sem_post(&sem);
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    
    pthread_t write[5], read[10];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&sem,1,0);

    int a[10]={1,2,3,4,5,6,7,8,9,10};

    for(int i = 0; i < 5; i++){
        pthread_create(&write[i],NULL,(void *)writer,(void *)&a[i]);
    }
    for(int i = 0; i < 10; i++){
        pthread_create(&read[i],NULL,(void *)reader,(void *)&a[i]);
    }

    for(int i = 0; i < 5; i++){
        pthread_join(write[i],NULL);
    }
    for(int i = 0; i < 10; i++){
        pthread_join(read[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);

    return 0;

}