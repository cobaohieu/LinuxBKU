#include <pthread.h>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>

struct sharedVariable {
    char *value1;
    int value2;

};
void *PrintHello(void * input){
    struct sharedVariable * newInput = (struct sharedVariable * ) input;
    printf("hello %s at thread %d\n", newInput->value1, newInput->value2);
    newInput->value2 += 1;
    newInput->value1 = "Computer";
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t threadID;
    struct sharedVariable input;
    input.value1 = "World";
    input.value2 = 1;
    pthread_create(&threadID, NULL, &PrintHello, (void *) &input);
    pthread_exit(NULL);
}