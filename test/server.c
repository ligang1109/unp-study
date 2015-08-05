#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <time.h>

#define MAXLINE 100

int main(int argc, char **argv)
{
    int listenfd, connfd;
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

    while (1) {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        close(listenfd);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));

        close(connfd);
    }
}
