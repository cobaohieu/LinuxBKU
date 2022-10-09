#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>


#define NUM_THREADS 5

void *RandomizeValue(void *){
    int value = rand() % 6 + 1;
    int *result = (int *) malloc(sizeof(int));
    *result = value;
    return (void *) result;
}

int main(int argc, char *argv[]){
    pthread_t threadIDs[NUM_THREADS];
    for (int i=0; i<NUM_THREADS; i++){
        pthread_create(&threadIDs[i], NULL, &RandomizeValue, (void *) NULL);
    }
    for (int i=0; i<NUM_THREADS; i++){
        int* response;
        pthread_join(threadIDs[i], (void **) &response);
        sleep(10);
        printf("DONE with random value: %d\n", *response);
    }
    pthread_exit(NULL);
}