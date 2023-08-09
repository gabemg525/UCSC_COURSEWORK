#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>


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

typedef struct {
    int seq;
    //char pointer and dynamically allocate size
    char* raw_packet;
}Sequence_packet;

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen, char* path, int mtu, int fp_bytes)
{
    int n;
    

    struct timeval tv;
    //change to 60 sec
    tv.tv_sec = 60;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        fputs("setsockopt error\n",stderr);
        exit(EXIT_FAILURE);
    }
    FILE *output;
    int seq_num = 0;
    output = fopen(path, "wb");
    

    
    printf("size of fp: %d\n", fp_bytes);
    int mtu_s = fp_bytes/mtu;

    printf("mtu's: %d\n", mtu_s);
    int bytes_left = fp_bytes - mtu_s*mtu;
    printf("bytes_left: %d\n", bytes_left);
    int m;
    printf("test1\n");
    char recvp_arr[mtu_s][mtu];
    printf("test1\n");
    Sequence_packet* seq_packet = (Sequence_packet*)malloc(sizeof(Sequence_packet));
    Sequence_packet* seqR_packet = (Sequence_packet*)malloc(sizeof(Sequence_packet));
    printf("test1\n");
    char* packet;
    
    

    printf("test1\n");
    int j;
    int i = 0;
    printf("test1\n");

    for (i=0; i<mtu_s;i++) {
        printf("test1\n");
        packet = (char*)malloc(mtu*sizeof(char));
        fread(packet, mtu, 1, fp);
        seq_packet->seq = i;
        
        seq_packet->raw_packet= packet;
        printf("packet client #%d - %s\n", seq_packet->seq, seq_packet->raw_packet);
        if((n = sendto(sockfd, seq_packet, sizeof(*seq_packet), 0, pservaddr, servlen))<0){
            // printf("n: %d\n", errno);
            // fputs("client send error\n",stderr);
            exit(EXIT_FAILURE);
        }
        // free(packet);
        if((n = recvfrom(sockfd, seqR_packet, MAXLINE, 0, NULL, NULL))<0){
            //ETIMEDOUT here?
            printf("ERROR TIMEOUT TEST\n");
            if(errno == 11){
                fputs("Cannot detect server\n",stderr);
                exit(EXIT_FAILURE);
            }
            
            exit(EXIT_FAILURE);
        }

        // printf("%d\n",n);
        // printf("\nraw_packet: %s\n",seqR_packet->raw_packet);
        
        // seqR_packet->raw_packet[n] = 0; 

        // recvpack = (char*)malloc(mtu*sizeof(char));
        
        seq_num = seqR_packet->seq;
        // recvp_arr[seq_num] = (char*)malloc(mtu*sizeof(char));
        
        
        // printf("recvpack: %s\n", recvpack);
        memcpy(recvp_arr[seq_num],seqR_packet->raw_packet,strlen(seqR_packet->raw_packet));
        
        // printf("rcv packet %s\n",recvp_arr[seq_num]);
        // fwrite(recvpack,mtu,1, output);
    }
    // free(seq_packet);
    // free(seqR_packet);
    // printf("\nReordering:\n");
    for(j = 0; j<i; j++){
        // printf("packet #%d: %s\n", j,recvp_arr[j]);
        fwrite(recvp_arr[j],mtu,1, output);
    }
    if(bytes_left>0){
        char last_packet[MAXLINE],last_recv[MAXLINE];
        // printf("bytes left: %d\n", bytes_left);
        // printf("bytes left over: %d\n", bytes_left);
        fread(last_packet, bytes_left, 1, fp);
        // printf("last packet client - %s\n", packet);
        if((n = sendto(sockfd, last_packet, sizeof(last_packet), 0, pservaddr, servlen))<0){
            // printf("n: %d\n", errno);
            // fputs("client send error\n",stderr);
            fputs("client sendto error\n",stderr);
            exit(EXIT_FAILURE);
        }
        if((n = recvfrom(sockfd, last_recv, MAXLINE, 0, NULL, NULL))<0){
            
            if(errno == 11){
                fputs("Cannot detect server\n",stderr);
                exit(EXIT_FAILURE);
            }
            fputs("client recvfrom error\n",stderr);
            exit(EXIT_FAILURE);
        }

        // printf("%d\n",n);
        last_recv[n] = 0; 

    
        fwrite(last_recv,bytes_left,1, output);
    }
    
    
    fclose(output);
}

int main(int argc, char **argv)
{
    int sockfd;
    
    struct sockaddr_in servaddr;
    if(argc > 6){
        fputs("usage: udpcli <IPaddress>",stderr);
        exit(EXIT_FAILURE);
    }
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fputs("socket error\n",stderr);
        exit(EXIT_FAILURE);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));

    if ((inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0){
        printf("inet_pton error for %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // loopback ip 127.0.0.1
    //convert mtu a better way atoi?
    //socklen_t mtu;
    
    int mtu = atoi(argv[3]);
    printf("mtu: %d\n", mtu);
    FILE *input;
    char inpath[MAXLINE+1];
    char outpath[MAXLINE+1];

    sprintf(inpath, "./%s", argv[4]);
    sprintf(outpath, "./%s", argv[5]);
    struct stat st;
    stat(inpath, &st);
    int infile_size = st.st_size;
    printf("%s\n",inpath);
    input = fopen(inpath, "rb"); 


    dg_cli(input, sockfd, (SA *) &servaddr, sizeof(servaddr), outpath, atoi(argv[3]),infile_size);
    fclose(input);
    exit(0);
    return 0;
}
