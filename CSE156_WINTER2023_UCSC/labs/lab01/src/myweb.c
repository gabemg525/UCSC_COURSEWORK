#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


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


int main( int argc, char *argv[] )      // Array of environment variable strings
{
    int count;

    int sockfd, n;
    struct sockaddr_in servaddr;
    if(argc > 4){
        printf("Error: not enough arguments");
        return 0;
    }
    
    

    char* url = argv[1];
    char* dst = argv[2];
    char* flag = argv[3];
    // printf("url: %s \ndst: %s\n", url, dst);
    // Display each command-line argument.
    // printf( "\nCommand-line arguments:\n" );
    // for( count = 0; count < argc; count++ )
    // printf( "  argv[%d]   %s\n", count, argv[count] );
        
    
    FILE *output, *head;
    head = fopen("head.txt", "w");
    output = fopen("./bin/output.dat", "w");
    // printf("test-1\n");
    char *ip_port, *ip, *port, *path;
    char buffer[MAXLINE + 1];

    ip_port = strtok(dst, "/");
    path = strtok(NULL,"");
    ip = strtok(ip_port,":");
    port = strtok(NULL,"");
    //printf("  hostname: %s ip: %s port: %s path to file: %s\n", url, ip, port, path);

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("socket error\n");
        return 0;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    if(port==NULL){
        servaddr.sin_port = htons(80); 
    }else{
        int port_i = atoi(port);
        servaddr.sin_port = htons(port_i); 
    }
    
    if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n", ip);
        return 0;
    }
    // servaddr.sin_addr = inet_pton(AF_INET, ip, &servaddr.sin_addr);
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0){
        printf("connect error\n");
        return 0;
    }

    if(flag==NULL){
        sprintf(buffer, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", path, url);
    }else{
        sprintf(buffer, "HEAD /%s HTTP/1.0\r\nHost: %s\r\n\r\n", path, url);
    }
    //printf("  \nbuffer: %s\n", buffer);
    if((n = write(sockfd, buffer, strlen(buffer)))<0){
        printf("write error\n");
        return 0;
    }
    //printf("test\n");
    char buff[MAXLINE+1];

    if(flag==NULL){
        if((n = read(sockfd, buff, MAXLINE))>0){
            buff[n] = 0;
            char* buff2, *buff1;//strcmp str

            buff1 = strtok(buff,"<");
            buff2 = strtok(NULL,"");
            fputs("<",output);
            if (fputs(buff2, output) == EOF){
                printf("fputs error");
                return 0;
            }
        }
    }

    while((n = read(sockfd, buff, MAXLINE))>0){

        buff[n] = 0;
        if(flag==NULL){
            if (fputs(buff, output) == EOF){
                printf("fputs error");
                return 0;
            }
        }else{
            if (fputs(buff, stdout) == EOF){
                printf("fputs error");
                return 0;
            }
        }
    }
    if(n<0){
        printf("read error\n");
        return 0;
    }
    fclose(head);
    fclose(output);
    exit(0);
    
    
    
    return 0;
}