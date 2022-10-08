#include <pthread.h>
#include <stdio.h>

void *PrintHello(void *inputString){
    char * castedInput = (char *) inputString;
    printf("Hello %s\n", castedInput);
    pthread_exit(NULL);
}

int main(){
    pthread_t threadID;
    const char *inputString = "World";
    int status = pthread_create(&threadID, NULL, &PrintHello, (void *) inputString);
    pthread_exit(NULL);
}