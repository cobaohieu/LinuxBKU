#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

pid_t pid_B;
pid_t pid_C;
pid_t pid_D;
void sig_par(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("PROCESS A RECEIVE SIGNAL FROM B, C, D AND SEND THE TERMINAL SIGNAL TO C, D...\n");
        sleep(1);
        kill(pid_C, SIGUSR1);
        kill(pid_D, SIGUSR2);
        exit(signo);
    }
}
void sig_child(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("PROCESS C RECEIVE SIGNAL FROM A...\n");
        exit(signo);
    }
    else if (signo == SIGUSR2)
    {
        printf("PROCESS D RECEIVE SIGNAL FROM A...\n");
        exit(signo);
    }
}

int main(void)
{
    pid_t ppid;
    ppid = getpid();
    pid_C = fork();
    if (pid_C == 0)
    {
        signal(SIGUSR1, sig_child);
        sleep(10);
    }
    pid_D = fork();
    if (pid_D == 0)
    {
        signal(SIGUSR2, sig_child);
        sleep(10);
    }
    pid_B = fork();
    if (pid_B == 0)
    {
        printf("PROCESS B SEND TERMINAL SIGNAL TO A...\n");
        sleep(1);
        kill(ppid, SIGUSR1);
        exit(0);
    }
    signal(SIGUSR1, sig_par);
    wait(NULL);
    return 0;
}