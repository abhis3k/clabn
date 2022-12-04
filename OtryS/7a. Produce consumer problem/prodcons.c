#include<stdio.h>
#include<stdlib.h>

int full=0, empty=10, x=0;
int mutex=1;

void producer(){
    --mutex;
    ++full;
    --empty;

    x++;
    printf("Produce produces item %d", x);

    ++mutex;
}

void consumer(){
    --mutex;
    --full;
    ++empty;

    x--;
    printf("Consumer consumes item %d", x);

    ++mutex;
}

int main(){

    int n,i;

    #pragma omp critical

    for(i=1; i>0; i++){

        printf("\nEnter your choice (1,2,3): ");
        scanf("%d", &n);

        switch(n){

            case 1:
                if((mutex==1) && (empty!=0)){
                    producer();
                } else {
                    printf("Buffer full");
                }
                
                break;
            
            case 2:
                if((mutex==1) && (full!=0)){
                    consumer();
                } else {
                    printf("Buffer empty");
                }
                
                break;
            
            case 3:
                exit(0);
                break;
        
        }

    }

    return 0;

}