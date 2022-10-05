#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
pid_t pid_C;
pid_t pid_B;
void sig_par(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("PROCESS A RECEIVE SIGNAL FROM C AND SEND THE TERMINAL SIGNAL TO B...\n");
        kill(pid_B, SIGUSR1);
        exit(signo);
    }
}
void sig_child(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("PROCESS B RECEIVE SIGNAL FROM A...\n");
        exit(signo);
    }
}
int main(void)
{
    pid_t ppid;
    ppid = getpid();
    pid_B = fork();
    if (pid_B == 0)
    {
        signal(SIGUSR1, sig_child);
        sleep(10);
    }
    pid_C = fork();
    if (pid_C == 0)
    {
        printf("PROCESS C SEND TERMINAL SIGNAL TO A...\n");
        sleep(1);
        kill(ppid, SIGUSR1);
        exit(0);
    }
    signal(SIGUSR1, sig_par);
    wait(NULL);
    return 0;
}