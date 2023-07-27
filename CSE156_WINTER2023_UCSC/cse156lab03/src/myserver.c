#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>

/* Miscellaneous constants */
#define MAXLINE 40000 /* max text line length */
#define BUFFSIZE 8192 /* buffer size for reads and writes */
/* Define some port number that can be used for our examples */
#define SERV_PORT 9877 /* TCP and UDP */
#define SERV_PORT_STR "9877" /* TCP and UDP */
#define UNIXSTR_PATH "/tmp/unix.str" /* Unix domain stream */
#define UNIXDG_PATH "/tmp/unix.dg" /* Unix domain datagram */
/* Following shortens all the typecasts of pointer arguments: */
#define SA struct sockaddr
#define HAVE_STRUCT_SOCKADDR_STORAGE

void delay(int tot_ms)
{

    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + tot_ms)
        ;
}

int random_percent(){
    int x =rand()/(RAND_MAX/100);
    return x;
}

char* RFC_time(void) {
    
    time_t now;
    time( &now );
    struct tm *gm = gmtime(&now);
    int hours, minutes, seconds, day, month, year;
    hours = gm->tm_hour;         
    minutes = gm->tm_min;        
    seconds = gm->tm_sec;        
    day = gm->tm_mday;            
    month = gm->tm_mon + 1;      
    year = gm->tm_year + 1900;   
    struct timeval tv;
    gettimeofday(&tv,NULL);

    int tm_since = (tv.tv_usec/1000);
    int s = tm_since/1000;
    int ms = tm_since - s*1000;
    char *buff;
    buff = (char*)malloc(MAXLINE*sizeof(char));
    sprintf(buff,"%04d-%02d-%02dT%02d:%02d:%02d.%03dZ", year, month, day, hours, minutes, seconds, ms);
   
    return buff;

}

struct arg_struct {
    int sockfd;
    const SA *pcliaddr;
    socklen_t clilen;
    int droppc;
};

char* cli_id[100];

int find_cli_id(char* head){

    char *buff = (char*)malloc(sizeof(char)*MAXLINE);
    int i, slash=0, buff_i=0;
    int l = strlen(head);
    //get the head without the segment size and seq number
    for(i = 0; i<l; i++){
        if(slash>1){
            buff[buff_i]=head[i];
            buff_i++;
        }
        if(head[i]=='/'){
            slash++;
        }
    }

    //if client id is set already, return the index from cli_id array, else return the next open
    for(i = 0; i<100; i++){
  
        // printf("cli_id[%d]: %s, head: %s\n", i, cli_id[i],head);
        if(strcmp(buff,cli_id[i])==0){
            // printf("same\n");
            return i;
        }else if(cli_id[i][0]=='o'){
            // printf("differ\n");
            cli_id[i] = buff;
            return i;
        }
    }
    return -1;
}

void dg_serv_read(int sockfd, SA *pcliaddr, socklen_t clilen, int droppc)
{
    int n;
    int i = 0;
    socklen_t len;
    char mesg[MAXLINE];
    FILE **output;
    output = (FILE**)malloc(100*sizeof(FILE*));
    char* head,**path,*curr_path;
    char ***to_write = (char***)malloc(100*sizeof(char**));
    
    path = (char**)malloc(100*sizeof(char*));
    unsigned int seq, seg_size, *total_p, mtu;
    unsigned int *ACKseq = (unsigned int*)malloc(2*sizeof(unsigned int));
    unsigned int len_head;
    unsigned int **seg_sz_arr = (unsigned int**)malloc(100*sizeof(unsigned int*));

    unsigned int *total_recvp = (unsigned int*)malloc(100*sizeof(unsigned int));
    bool **recv_arr = (bool**)malloc(100*sizeof(bool*));
    total_p = (unsigned int*)malloc(sizeof(unsigned int)*100);
    int percent_to_beat;
    int z;
    for(i=0;i<100;i++){
        cli_id[i] = (char*)malloc(sizeof(char)*MAXLINE);
        cli_id[i][0]='o';
    }
    
    while (1) {
        recv_wait:
        len = clilen;

        // printf("waiting to receive\n");
        if((n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len))<0){
            fputs("server recvfrom error",stderr);
            exit(EXIT_FAILURE);
        }

        head = strtok(mesg,"\n");
        
        int c_id=find_cli_id(head);
        // printf("cli_id: %d\n", c_id);
        len_head = strlen(head);
        
        // printf("head: %s\n", head);
        seq = atoi(strtok(head,"/"));
        
        if(droppc >= random_percent()){
            printf("%s, DROP DATA, %d\n", RFC_time(), seq);
            continue;
        }
        if(droppc >= random_percent()){
            printf("%s, DROP ACK, %d\n", RFC_time(), seq);
            continue;
        }
        printf("%s, DATA, %d\n", RFC_time(), seq);
        // free(time_rfc);

        seg_size = atoi(strtok(NULL,"/"));
        if(total_recvp[c_id]==0){
            total_p[c_id] = atoi(strtok(NULL,"/"));
            mtu = atoi(strtok(NULL,"/"));
            path[c_id] = (char*)malloc(sizeof(char)*MAXLINE);
            curr_path = strtok(NULL,"");
            strcpy(path[c_id], curr_path);
            to_write[c_id] = (char**)malloc(sizeof(char*) * total_p[c_id]);
            seg_sz_arr[c_id] = (unsigned int*)malloc(sizeof(unsigned int) * total_p[c_id]);
            recv_arr[c_id] = (bool*)malloc(sizeof(bool) * total_p[c_id]);
            memset(recv_arr[c_id],0,total_p[c_id] * sizeof(*recv_arr[c_id])); 
        }

        ACKseq[0] = seq;
        ACKseq[1] = c_id;
 
        printf("%s, ACK, %d\n", RFC_time(), seq);
        if((sendto(sockfd, ACKseq, sizeof(int)*2, 0, pcliaddr, len))<0){
            fputs("server sendto error",stderr);
            exit(EXIT_FAILURE);
        }
        if(recv_arr[c_id][seq]==false){
            // printf("seq %d not found, storing in array\n", seq);
            recv_arr[c_id][seq]=true;
            total_recvp[c_id]++;
            to_write[c_id][seq] = (char*)malloc(seg_size*sizeof(char));
        
            for(i = 0; i < seg_size; i++){
                to_write[c_id][seq][i]=mesg[i+len_head+1];
            }
            seg_sz_arr[c_id][seq] = seg_size;
            // printf("to_write[i]: %s\nseg_sz: %d\n",to_write[seq],seg_sz_arr[seq]);
        }
        
        
        if(total_recvp[c_id]== total_p[c_id]){

            
            output[c_id] = fopen(path[c_id], "wb");
            for(z=0; z<total_p[c_id]; z++){
  
                if((n=fwrite(to_write[c_id][z],seg_sz_arr[c_id][z],1,output[c_id]))<0){
                    fputs("server fwrite error\n",stderr);
                    exit(EXIT_FAILURE);
                }
            }
            
            free(to_write[c_id]);
            free(seg_sz_arr[c_id]);
            free(recv_arr[c_id]);
            fclose(output[c_id]);
            // free(output);
            // cli_id[c_id]="o";
            total_recvp[c_id] = 0;
            
        }
        
        // printf("where seg?\n");
    } 
    printf("exited rcv loop\n");
    

    return;
}

int main(int argc, char **argv)
{

    int sockfd;
    if(argc > 3){
        printf("Error: not enough arguments\n");
        return 0;
    }




    struct sockaddr_in servaddr, cliaddr;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0){
        fputs("client socket error\n",stderr);
        exit(EXIT_FAILURE);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    bind(sockfd, (SA *) &servaddr, sizeof(servaddr));


    

    dg_serv_read(sockfd, (SA *) &cliaddr, sizeof(cliaddr), atoi(argv[2]));
    exit(0);
    return 0;
}
