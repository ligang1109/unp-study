#include <signal.h>
#include <stdio.h>

static void sigUsr(int signo)
{
    if (signo == SIGUSR1) {
        printf("received SIGUSR1\n");
    } else if (signo == SIGUSR2) {
        printf("received SIGUSR2\n");
    } else {
        printf("received signal %d\n", signo);
    }
}

int main(int argc, char **argv)
{
    int i;

    signal(SIGUSR1, sigUsr);
    signal(SIGUSR2, sigUsr);

    for (i = 0; i < 100000; i++) {
        printf("%d\n", i);
        sleep(3);
    }
}
