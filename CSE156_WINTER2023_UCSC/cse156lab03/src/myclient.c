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
#include <pthread.h>
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
    // Converting time into milli_seconds

 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + tot_ms)
        ;
}

char* RFC_time() {
    
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

pthread_mutex_t mutex;
int *ACKwin;

int basesn=0, nextsn, win_end_sn, signal=0, total_sn;

void* dg_cli_rcv(void *sockfd){
    int ACKseq, n, ACK_c_id, last_ACK_c_id;
   
    unsigned int *ACKseq_unsigned = (unsigned int*)malloc(2*sizeof(unsigned int));
    
    
    while(1){
        if(signal==1){printf("end signal\n");return;}
        if(((n = (recvfrom(sockfd, ACKseq_unsigned, sizeof(int)*2, 0, NULL, NULL))))<0){
                    //ETIMEDOUT here?
            printf("\n");
            if(errno == 11){           
            }else{
                fputs("client recvfrom error",stderr);
                exit(EXIT_FAILURE);
            }   
        }
        
        pthread_mutex_lock(&mutex);
        if(n>=0){
            
            ACKseq = ACKseq_unsigned[0];  
            ACK_c_id = ACKseq_unsigned[1];
            ACKwin[ACKseq]=1;

            // printf("ACK c_id: %d\n", ACKseq_unsigned[1]);
        }
        // printf("ACKwin[%d]: %d\n",ACKseq, ACKwin[ACKseq]);
        
        char* time_rfc;
        time_rfc = (char*)malloc(MAXLINE*sizeof(char));
        time_rfc = RFC_time();
        if(ACKseq+1>total_sn-1){
            nextsn=ACKseq;
        }else{
            nextsn = ACKseq+1;
        }    
            
        printf("%s, ACK, %d, %d, %d, %d\n", time_rfc, ACKseq, basesn, nextsn,win_end_sn);
        free(time_rfc);

        pthread_mutex_unlock(&mutex);
    }
}

struct arg_struct {
    FILE* fp; 
    int sockfd;
    const SA *pservaddr;
    socklen_t servlen;
    char* path;
    unsigned int mtu;
    unsigned int winsz;
    unsigned int fp_bytes;
};

void* dg_cli(void *arguments){

    struct arg_struct *args = arguments;
    // FILE* fp, int sockfd, const SA *pservaddr, socklen_t servlen,
    // char* path, unsigned int mtu, unsigned int winsz, unsigned int fp_bytes
    FILE* fp = args->fp; 
    int sockfd = args->sockfd;
    const SA *pservaddr = args->pservaddr;
    socklen_t servlen = args->servlen;
    char* path = args->path;
    unsigned int mtu = args->mtu;
    unsigned int winsz = args->winsz;
    unsigned int fp_bytes = args->fp_bytes;

    int n;

    unsigned int total_mtu = fp_bytes/mtu;
    unsigned int bytes_left = fp_bytes - total_mtu*mtu;
    unsigned int packets_to_send = 0;
    
    if(bytes_left>0){
        packets_to_send=total_mtu+1;
    }else{
        packets_to_send=total_mtu;
    }
    // printf("packets to send: %d\n", packets_to_send);
    

    
    // printf("fp_bytes: %d\nbytes_left: %d\n",fp_bytes,bytes_left);
    unsigned int j,g,h,tot_transmissions;
    unsigned int i = 0;
    unsigned int seg_size = mtu;
    char* seq_num;
    
    
    unsigned int len_head;
    
    unsigned int *ACKseq_unsigned = (unsigned int*)malloc(sizeof(unsigned int));
    int ACKseq = -1;
    
    
    int pktsn=0;
    total_sn=packets_to_send;
    //does retransmit number have to be by packet or buy window
    if(winsz>total_sn){
        win_end_sn = total_sn;
    }else{
        win_end_sn = winsz;
    }
    pthread_mutex_lock(&mutex);
    ACKwin = (int*)malloc(total_sn*sizeof(int));
    for(i=0; i<total_sn; i++){
        ACKwin[i]=0;
    }
    pthread_mutex_unlock(&mutex);
    char **packet = (char**)malloc(sizeof(char*)*(win_end_sn-basesn));
    while(1) {
       
        while(ACKwin[basesn]==1){
            if(basesn==total_sn-1){
                signal = 1;
                return;
            }
            basesn++;
            
        }
        int win_sn = 0;
        
        if(basesn+winsz>total_sn){
            win_end_sn = total_sn-1;
        }else{
            win_end_sn = basesn+winsz-1;
        }
        for(pktsn=basesn;pktsn<=win_end_sn;pktsn++){
            char* contents;
            //adjust segment size for last packet
            if(pktsn==packets_to_send-1&&bytes_left>0){
                contents = (char*)malloc(bytes_left*sizeof(char));
                if((n=fread(contents, bytes_left, 1, fp))<0){
                    fputs("client fread error\n",stderr);
                    exit(EXIT_FAILURE);
                }
                seg_size = bytes_left;
                goto jump;   
            }

            contents = (char*)malloc(mtu*sizeof(char));
            if((n=fread(contents, mtu, 1, fp))<0){
                fputs("client fread error\n",stderr);
                exit(EXIT_FAILURE);
            }
            seg_size = mtu;
 
            jump:
            packet[win_sn] = (char*)malloc(sizeof(char)*MAXLINE);
            char* head_data;
            
            head_data = (char*)malloc((MAXLINE-seg_size)*sizeof(char));
            // printf("%s\n",path);
            // printf("seg size: %d\n", seg_size);
            sprintf(head_data,"%d/%d/%d/%d/%s\n", pktsn, seg_size, packets_to_send, mtu, path);
            len_head = strlen(head_data);
            // store head data followed by contents in the packet
            
            for(j = 0; j < seg_size+len_head; j++){
                if(j<strlen(head_data)){
                    packet[win_sn][j]=head_data[j];
                }else{
                    packet[win_sn][j]=contents[j-len_head];
                }
            }
            win_sn++;
        }

        win_sn = 0;
        int tot_ret = 0;
        retrans_window:
        if(tot_ret>5){
            fputs("Reached max re-transmission limit\n",stderr);
            exit(EXIT_FAILURE);
        }
        for(pktsn=basesn;pktsn<=win_end_sn;pktsn++){
            // printf("packet[win_sn]: %s\n", packet[win_sn]);
            if((n = sendto(sockfd, packet[win_sn], MAXLINE, 0, pservaddr, servlen))<0){
            
                fputs("client sendto error\n",stderr);
                exit(EXIT_FAILURE);
            }
            char* time_rfc;
            time_rfc = (char*)malloc(MAXLINE*sizeof(char));
            time_rfc = RFC_time();
            if(pktsn+1>total_sn-1){
                nextsn=pktsn;
            }else{
                nextsn = pktsn+1;
            }    
            printf("%s, DATA, %d, %d, %d, %d\n", time_rfc, pktsn, basesn, nextsn,win_end_sn);
            free(time_rfc);
            delay(10);
       
            win_sn++;
            
            
        }
        for(g=basesn;g<=win_end_sn;g++){
            pthread_mutex_lock(&mutex);
            if(ACKwin[g]==0){  
                pthread_mutex_unlock(&mutex);
                win_sn = 0;
                tot_ret++;
                goto retrans_window;
            }
            pthread_mutex_unlock(&mutex);
        }
        for(int y=0; y<win_end_sn-basesn; y++){
            free(packet[y]);
        }
    }
    printf("return?\n");
    signal = 1;
    return;
}







int main(int argc, char **argv)
{

    int sockfd;
    
    struct sockaddr_in servaddr;
    if(argc > 7){
        fputs("usage: udpcli <IPaddress>",stderr);
        exit(EXIT_FAILURE);
    }
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fputs("client socket error\n",stderr);
        exit(EXIT_FAILURE);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));

    if ((inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0){
        printf("inet_pton error for %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    

 

    FILE *input;
    char inpath[MAXLINE+1];
    char outpath[MAXLINE+1];

    sprintf(inpath, "./%s", argv[5]);
    sprintf(outpath, "./%s", argv[6]);
    struct stat st;
    stat(inpath, &st);
    unsigned int infile_size = st.st_size;
    // printf("%d\n",infile_size);
    // printf("%s\n",inpath);
    input = fopen(inpath, "rb"); 

    struct timeval tv;
    //change to 60 sec
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    if ((setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv))) < 0) {
        fputs("setsockopt error\n",stderr);
        exit(EXIT_FAILURE);
    }
    
    int winsz = atoi(argv[4]);
    
    pthread_t t1, t2;

    struct arg_struct args;

    args.fp=input; 
    args.sockfd=sockfd;
    args.pservaddr=(SA *) &servaddr;
    args.servlen=sizeof(servaddr);
    args.path=outpath;
    args.mtu=atoi(argv[3]);
    args.winsz=winsz;
    args.fp_bytes=infile_size;

    
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&t1, NULL, &dg_cli_rcv, (void*)sockfd)!=0){
        fputs("pthread_create error\n",stderr);
        exit(EXIT_FAILURE);
        return 1;
    }
    if (pthread_create(&t2, NULL, &dg_cli, (void*)&args)!=0){
        fputs("pthread_create error\n",stderr);
        exit(EXIT_FAILURE);
        return 2;
    }
    if (pthread_join(t1,NULL)!=0){
        fputs("pthread_join error\n",stderr);
        exit(EXIT_FAILURE);
        return 3;
    }
    if (pthread_join(t2,NULL)!=0){
        fputs("pthread_join error\n",stderr);
        exit(EXIT_FAILURE);
        return 4;
    }

    // pthread_mutex_destroy(&mutex);

    
    
    // dg_cli(input, sockfd, (SA *) &servaddr, sizeof(servaddr), outpath, atoi(argv[3]), atoi(argv[4]), infile_size);
    pthread_mutex_destroy(&mutex);
    fclose(input);

    exit(0);

    return 0;
}


