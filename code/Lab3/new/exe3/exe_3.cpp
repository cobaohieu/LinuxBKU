#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>


int main()
{
    pid_t pid, pid1, pid2, pid3, pid4, pid5, pid6;
    pid = fork();

    if (pid == 0)
    {
        printf("Process B %d...\n", getpid());
        sleep(2);
    }
    else
    {
        pid1 = fork();
        if (pid1 == 0)
        {
            pid3 = fork();
            if (pid3 == 0)
            {
                pid5 = fork();
                if (pid5 == 0)
                {
                    sleep(1);
                    printf("Process F %d...\n", getpid());
                    exit(0);
                }
                pid6 = fork();
                if (pid6 == 0)
                {
                    sleep(2);
                    printf("Process G %d...\n", getpid());
                    exit(0);
                }
                printf("Process E %d...\n", getpid());
                sleep(6);
                // wait(NULL);
                exit(0);
            }
            printf("Process C %d...\n", getpid());
            sleep(4);
            exit(0);
        }
        else
        {
            pid2 = fork();
            if (pid2 == 0)
            {
                printf("Process D %d...\n", getpid());
                sleep(5);
                exit(0);
            }
            printf("Process A %d\n", getpid());
            sleep(3);
            exit(0);
        }
    }
    return 0;
}