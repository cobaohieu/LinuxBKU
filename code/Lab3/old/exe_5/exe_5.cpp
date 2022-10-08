#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

// Driver code
int main()
{
    pid_t pid, pid1, pid2, pid3, pid4, pid5, pid6;
    pid = fork();

    if (pid == 0) {
        printf("Process B %d...\n", getpid());
    }
  
    else {
        pid1 = fork();
        if (pid1 == 0) {
            pid3 = fork();
            if (pid3 == 0){
                pid5 = fork();
                if (pid5==0){
                    sleep(5);
                    printf("Process F %d...\n", getpid());
                }
                else {
                    pid6 = fork();
                    if (pid6==0){
                        sleep(6);
                        printf("Process G %d...\n", getpid());
                    }
                    else {
                        sleep(4);
                        printf("Process E %d...\n", getpid());
                    }
                }
            }
            else {
                sleep(2);
                printf("Process C %d...\n", getpid());
            }
        }
        else {
            pid2 = fork();
            if (pid2 == 0) {
                sleep(3);
                printf("Process D %d...\n", getpid());
            }
            else {
                sleep(1);
                printf("Process A %d\n", getpid());
            }
        }
    }
  
    return 0;
}