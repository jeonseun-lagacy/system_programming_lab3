#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo);
int i;
void main()
{
    struct sigaction act;
    i = 0;
    act.sa_handler = handler;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);
    printf("SIGINT on\n");

    while(1){
        sleep(1);
        printf("sleep for %d sec\n", ++i);
    }
}

void handler(int signo){
    printf("시그널 핸들러 작동\n");
    printf("signo : %d\n", signo);
    i = 0;
}