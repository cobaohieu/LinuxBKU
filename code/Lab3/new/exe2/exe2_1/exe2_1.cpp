#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// int main(void){
int main(){
    pid_t pid_B = fork();
    if (pid_B == 0){
        sleep(1);
        printf("Child B: %d\n", getpid());
        exit(0);
    }
    pid_t pid_C = fork();
    if (pid_C == 0){
        sleep(2);
        printf("Child C: %d\n", getpid());
        exit(0);
    }
    printf("Parent: %d\n", getpid());
    sleep(5);
    // wait(NULL);
    return 0;
}