#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

/* Miscellaneous constants */
#define MAXLINE 4096 /* max text line length */
#define BUFFSIZE 8192 /* buffer size for reads and writes */
/* Define some port number that can be used for our examples */
#define SERV_PORT 9877 /* TCP and UDP */
#define SERV_PORT_STR "9877" /* TCP and UDP */
#define UNIXSTR_PATH "/tmp/unix.str" /* Unix domain stream */
#define UNIXDG_PATH "/tmp/unix.dg" /* Unix domain datagram */
/* Following shortens all the typecasts of pointer arguments: */
#define SA struct sockaddr
#define HAVE_STRUCT_SOCKADDR_STORAGE

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
    int n;
    int i = 0;
    socklen_t len;
    unsigned char mesg[MAXLINE];

    for ( ; ; ) {
        // printf("send line server - \n");
        len = clilen;
        // printf("TEST_2\n");
        if((n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len))<0){
            fputs("server recvfrom error",stderr);
            exit(EXIT_FAILURE);
        }
        



        if((sendto(sockfd, mesg, n, 0, pcliaddr, len))<0){
            fputs("server sendto error",stderr);
            exit(EXIT_FAILURE);
        }
    } 
}

int main(int argc, char **argv)
{
    int sockfd;
    if(argc > 2){
        printf("Error: not enough arguments\n");
        return 0;
    }
    struct sockaddr_in servaddr, cliaddr;
    printf("test server\n");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
    exit(0);
    return 0;
}

