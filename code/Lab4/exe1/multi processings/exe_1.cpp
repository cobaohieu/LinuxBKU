#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

// int main(void){
int main(){
    double piValue{};
    double averagePi{};
    int status;

    pid_t pid_B, pid_C;
    double pi{};

    pid_B = fork();
    if (pid_B == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid_B == 0){
        printf("Child B: %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
    
    pid_C = fork();
    if (pid_C == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid_C == 0){
        printf("Child C: %d\n", getpid());
        exit(EXIT_SUCCESS);
    }
    do {
        pid_C = waitpid(pid_B, &status, WUNTRACED | WCONTINUED);
        if (pid_C == -1){
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (pid_C == 0){
            sleep(5);
            printf("Child C: %d\n", getpid());
            exit(EXIT_SUCCESS);
        }
        if  (WIFEXITED(status)){
            printf("exited, status = %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)){
            printf("killed by signal = %d\n", WTERMSIG(status));
        }
        else if(WIFSTOPPED(wstatus)){
            printf("stopped by signnal = %d\n", WSTOPSIG(status));
        }
        else if (WIFCONTINUED(status)){
            printf("continued");
        }

    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    exit(EXIT_SUCCESS);
    // printf("Parent: %d\n", getpid());
    // sleep(1);
    // wait(NULL);
    return 0;
}