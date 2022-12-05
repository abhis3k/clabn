#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

sem_t phil[N], mutex;
int state[N];

void test(int i){
    if(state[i]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING){
        state[i]=EATING;
        printf("EATING: Philosopher %d is taking forks %d and %d\n", i+1, LEFT+1, i+1);
        sem_post(&phil[i]);
    }
}

void take_fork(int i){
    sem_wait(&mutex);
    state[i]=HUNGRY;
    printf("HUNGRY: Philosopher %d is hungry\n", i+1);
    test(i);
    sem_post(&mutex);
    sem_wait(&phil[i]);
}

void put_fork(int i){
    sem_wait(&mutex);
    state[i]=THINKING;
    printf("THINKING: Philosopher %d is putting forks %d and %d\n", i+1, LEFT+1, i+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *i){
    int id = *(int *)i;
    take_fork(id);
    put_fork(id);
}

int main(){
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    pthread_t thread[10];

    sem_init(&mutex,0,1);
    for(int i=0; i<N; i++){
        sem_init(&phil[i],0,0);
    }

    for(int i=0; i<10; i++){
        pthread_create(&thread[i],NULL,(void *)philosopher,(void *)&a[i]);
    }
    for(int i=0; i<10; i++){
        pthread_join(thread[i],NULL);
    }

    return 0;
}