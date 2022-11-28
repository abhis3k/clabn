
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for constants and data types
#include <time.h> // data types to represent time
#include <sys/types.h> //has data types 
#include <sys/ipc.h>  // data types for shared memory
#include <sys/shm.h> // for shmat() and shmdt()
#include <stdbool.h> // for using boolean
#include <sys/time.h> // getimeofday() function

#define buffer_size 8 

int shmid1, shmid2;
int shmid3, shmid4;
bool* flag_memory;
int* turn_memory;
int* buffer_memory;

int getrandom(int n) 
{
	time_t t;
// set the range of random number based on time. 
	srand((unsigned)time(&t));
// crate random number and return it
	return (rand() % n + 1);
}
time_t gettime()
{
// timer to check for busy waiting
struct timeval t;
gettimeofday(&t, NULL);
time_t time=  t.tv_sec;
return time;
}
int main()
{
// creating shared memory (critical section)
// shared memory for flag varible
	shmid1 = shmget(5354, sizeof(bool) * 2, IPC_CREAT | 0660); 
// shared memory for turn
	shmid2 = shmget(1232, sizeof(int) * 1, IPC_CREAT | 0660); 
// shared memory for buffer
	shmid3 = shmget(4232, sizeof(int) * buffer_size, IPC_CREAT | 0660); 
//shared memory used by the timer
	shmid4 = shmget( 5633, sizeof(int) * 1, IPC_CREAT | 0660); 
// checking if the critical section is created successfully
	if (shmid1 < 0 || shmid2 < 0 || shmid3 < 0 || shmid4 < 0) {
		printf("Creation failed: ");
		exit(1);
	}
// gettting time
	time_t t1, t2;
	t1 =gettime();

// initalizing a empty array to store products
	buffer_memory = (int*)shmat(shmid3, NULL, 0);
	int num = 0;
	while (num < buffer_size) 
		buffer_memory[num++] = 0;

// get data from the critical section
	int* current_state = (int*)shmat(shmid4, NULL, 0);
	*current_state = 1;
	int wait_time;
	int i = 0; 
	int j = 1; 

// creating producer process with fork()
	pid_t a =fork(); // creating two process with fork
	if (a<0){
	perror("Creating producer and consumer failed");
	exit(1);
	}
	if (a>0)  // producer process 
	{
// fetching values from critical section
		flag_memory = (bool*)shmat(shmid1, NULL, 0);
		turn_memory = (int*)shmat(shmid2, NULL, 0);
		buffer_memory = (int*)shmat(shmid3, NULL, 0);
		if (flag_memory == (bool*)-1 || turn_memory == (int*)-1 || buffer_memory == (int*)-1) {
			perror("Producer can't be created: ");
			exit(1);
		}

		bool* flag = flag_memory;
		int* turn = turn_memory;
		int* buf = buffer_memory;
		int index = 0;
// implementing  Peterson's Algorithm
		while (*current_state == 1) {
			flag[j] = true;
			printf("Producer is ready now.\n\n");
			*turn = i;
			while (flag[i] == true && *turn == i);
// creating a product with random numbers	
			index = 0;
			while (index < buffer_size) {
				if (buf[index] == 0) {
					int temp = getrandom(buffer_size * 3);
					printf("The product %d have been produced and is ready to be consumed\n", temp);
					buf[index] = temp;
					break;
				}
				index++;
			}
// caecking if the array is full
			if (index == buffer_size)
				printf("The producer has produced the produccts to maximum capacity\n");
			printf("Products: ");
			index = 0;
			while (index < buffer_size)
				printf("%d ", buf[index++]);
			printf("\n");
			
// exiting section
			flag[j] = false;
			if (*current_state == 0)
				break;
			wait_time = getrandom(2);
			printf("Producer will wait for %d seconds\n\n", wait_time);
			sleep(wait_time);
		}
		exit(0);
	}
	else // consumer process 
	{
// getting data from critical region
		flag_memory = (bool*)shmat(shmid1, NULL, 0);
		turn_memory = (int*)shmat(shmid2, NULL, 0);
		buffer_memory = (int*)shmat(shmid3, NULL, 0);
		if (flag_memory == (bool*)-1 || turn_memory == (int*)-1 || buffer_memory == (int*)-1) {
			perror("Consumer shared memory error");
			exit(1);
		}

		bool* flag = flag_memory;
		int* turn = turn_memory;
		int* buf = buffer_memory;
		int index = 0;
		flag[i] = false;
		sleep(5);
// implementing  Peterson's Algorithm
		while (*current_state == 1) {
			flag[i] = true;
			printf("Consumer can consumer produts.\n\n");
			*turn = j;
			while (flag[j] == true && *turn == j)
				;

// checking if products are available for consumption
			if (buf[0] != 0) {
				printf("Job %d has been consumed\n", buf[0]);
				buf[0] = 0;
				index = 1;
				while (index < buffer_size) 
				{
					buf[index - 1] = buf[index];
					index++;
				}
				buf[index - 1] = 0;
			} else
				printf("NO products available to the consumer to be consumed\n");
			printf("Buffer: ");
			index = 0;
			while (index < buffer_size)
				printf("%d ", buf[index++]);
			printf("\n");

//exit section
			flag[i] = false;
			if (*current_state == 0)
				break;
			wait_time = getrandom(15);
// time consumer need to wait to get new products
			printf("Consumer will nedd to wait for %d seconds to get products to be consumed.\n\n", wait_time);
			sleep(wait_time);
		}
		exit(0);
	}
//busy waiting
	while (1) {
		t2 = gettime();
// set current_state to 0 if process waits longer than 10 seconds.
		if (t2 - t1 > 10) 
		{
			*current_state = 0;
			break;
		}
	}
// exit if too much time on busy waiting.
	wait();
	wait();
	printf("Too much time has passed.\n");
	return 0;
}


