#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAXLINE 100

int main(int argc, char **argv)
{
    int listenfd, connfd, pid, r;
    struct sockaddr_in servaddr;
    char buff[MAXLINE + 1];
    time_t ticks;

    if (argc != 2) {
        printf("usage %s port\n", argv[0]);
        exit(1);
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listenfd, 1024);

    pid = fork();

    if (pid == 0) {
        r = execl("/home/ligang/devspace/unp-study/test/worker", "worker", argv[1], (char *) 0);
        if (r < 0) {
            printf("%d\n", r);
        }
    }

    while (1) {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "master %.24s\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));

        close(connfd);
    }
}
