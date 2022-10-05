#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <csignal>

void sig_handler(int signum)
{
    printf("From child\n");
}

int main()
{
    pid_t pid, pid1;
    pid = fork();
    if (pid == 0)
    {
        sleep(2);
        printf("\nThis is process B with PID: %d\n", getpid());
    }
    else
    {
        pid1 = fork();
        if (pid1 == 0)
        {
            sleep(3);

            printf("\nThis is process C with PID: %d\n", getpid());
        }
        else
        {
            sleep(1);
            printf("\nThis is process A with PID: %d\n", getpid());
        }
    }
    return 0;
}
