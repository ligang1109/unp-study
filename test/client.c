#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <strings.h>

#define MAXLINE 100

int main(int argc, char **argv)
{
    int sockfd, n, err;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 3) {
        printf("usage %s ip port\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    err = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("err: %d\n", err);

    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}
