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
#include "myclientserver.h"


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







pthread_mutex_t mutex;






struct arg_struct {

    char** packet_arr;
    char outpath[MAXLINE+1];
    unsigned int packets_to_send;
    int port;
    char ip[MAXLINE+1];
    unsigned int winsz;

};

struct ip_port {

    char** ip;
    int* port;

};

unsigned int serv_n_global=0, total_servers_down=0;

struct ip_port configure_servaddr(char* servaddrfile, unsigned int servn){
    struct ip_port to_return;
    to_return.ip = (char**)malloc(sizeof(char*)*(servn));
    to_return.port = (int*)malloc(sizeof(int*)*(servn));
    FILE* config = fopen(servaddrfile,"r");
    

    unsigned int i;
    for(i=0; i<servn; i++){
        char buff[MAXLINE+1];
        fgets(buff, MAXLINE+1, config);
        to_return.ip[i] =  (char*)malloc(sizeof(char)*(MAXLINE+1));
        strcpy(to_return.ip[i],strtok(buff," "));
        to_return.port[i] = atoi(strtok(NULL,""));
    }
    fclose(config);
    return to_return;
    
}

void* dg_cli(void *arguments){
    struct arg_struct *args = arguments;
    char** packet_arr = args->packet_arr;
    char* outpath = args->outpath;
    unsigned int packets_to_send = args->packets_to_send;
    unsigned int winsz = args->winsz;
    
    int port = args->port;
    char* ip = args->ip;
    unsigned int *ACK_arr = (unsigned int*)malloc(sizeof(unsigned int)*packets_to_send);
    char buff[MAXLINE];
    unsigned int *ACKsn = (unsigned int*)malloc(sizeof(unsigned int)*2);
    int sockfd, n;
    struct sockaddr_in servaddr;

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fputs("client socket error\n",stderr);
        pthread_mutex_lock(&mutex);
        total_servers_down+=1;
        pthread_mutex_unlock(&mutex);
        return;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);



    if ((inet_pton(AF_INET, ip, &servaddr.sin_addr)) <= 0){
        sprintf(buff,"inet_pton error for %s\n", ip);
        fputs(buff,stderr);
        pthread_mutex_lock(&mutex);
        total_servers_down+=1;
        pthread_mutex_unlock(&mutex);
        return;
    }

    struct timeval tv;
    //change to 60 sec
    tv.tv_sec = 0;
    tv.tv_usec = 10000;
    
    if ((setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv))) < 0) {
        fputs("setsockopt error\n",stderr);
        pthread_mutex_lock(&mutex);
        total_servers_down+=1;
        pthread_mutex_unlock(&mutex);
        return;
    }
    const SA *pservaddr=(SA *) &servaddr;
    socklen_t servlen=sizeof(servaddr);
    unsigned int sn, basesn=0, nextsn, win_end_sn, signal=0, total_sn, x, i, end_signal, ACKnextsn;
    for(i=0;i<packets_to_send;i++){
        ACK_arr[i]=0;
    }
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    printf("ip: %s port: %d\n", ip, ntohs(servaddr.sin_port));
    int check_connect = connect(sockfd, (struct sockaddr *)&servaddr, servlen);
    int lport;
    if (getsockname(sockfd, (struct sockaddr *)&sin, &len) == -1)
        perror("getsockname");
    else
        lport=ntohs(sin.sin_port);

    unsigned int total_retrans = 0;
    //sn, seg size, packets_to_send, path
    while(1){
        total_retrans = 0;
        while(ACK_arr[basesn]==1){
            if(basesn==packets_to_send-1){
                end_signal = 1;
                pthread_mutex_lock(&mutex);
                serv_n_global-=1;
                pthread_mutex_unlock(&mutex);
                return;
            }
            basesn++;
            
        }
        
        
        if(basesn+winsz>packets_to_send){
            win_end_sn = packets_to_send-1;
        }else{
            win_end_sn = basesn+winsz-1;
        }

       
        transmit:

        for(sn=basesn;sn<=win_end_sn;sn++){
            // printf("packet_arr[%d]:\n%s\n",sn, packet_arr[sn]);
            delay(10);
            if((n = sendto(sockfd, packet_arr[sn], MAXLINE, 0, pservaddr, servlen))<0){

                fputs("client sendto error\n",stderr);
                pthread_mutex_lock(&mutex);
                total_servers_down+=1;
                pthread_mutex_unlock(&mutex);
                return;
            }
          
            char* time_rfc;
            time_rfc = (char*)malloc(MAXLINE*sizeof(char));
            time_rfc = RFC_time();
            if(sn+1>packets_to_send-1){
                nextsn=sn;
            }else{
                nextsn = sn+1;
            }    
            printf("%s, DATA, %d, %s, %d, %d, %d, %d, %d\n", time_rfc, lport, ip, port, sn, basesn, nextsn,win_end_sn);
            if(((n = (recvfrom(sockfd, ACKsn, sizeof(int)*2, 0, NULL, NULL))))<0){
                    //ETIMEDOUT here?
                if(errno == 11){      
                    goto ACK_skip;     
                }else{
                    fputs("\n\n\n\nclient recvfrom error\n\n\n\n",stderr);
                    pthread_mutex_lock(&mutex);
                    total_servers_down+=1;
                    pthread_mutex_unlock(&mutex);
                    return;
                }   
            
            }
            ACK_arr[ACKsn[0]]=1;
            if(ACKsn[0]>=packets_to_send-1){
                ACKnextsn=ACKsn[0];
            }else{
                ACKnextsn = ACKsn[0]+1;
            }    
            printf("%s, ACK, %d, %s, %d, %d, %d, %d, %d\n", time_rfc, lport, ip, port, ACKsn[0], basesn, nextsn,win_end_sn);
            ACK_skip:
            free(time_rfc);
        }
        for(sn=basesn;sn<=win_end_sn;sn++){
            if(ACK_arr[sn]==0){
                if(total_retrans>9){
    
            
                    total_servers_down+=1;
                    if(total_servers_down>=serv_n_global){
                        fputs("Reached max re-transmission limit\n", stderr);
                        exit(EXIT_FAILURE);
                    }
        
                    pthread_mutex_unlock(&mutex);
                    return;
                    
                }
                fputs("Packet loss detected\n", stderr);
                total_retrans++;

                goto transmit;
            }
        }
        
    }
    pthread_mutex_lock(&mutex);
    serv_n_global-=1;
    pthread_mutex_unlock(&mutex);
    return;
    
}






int main(int argc, char **argv)
{


    int n;
    

    if(argc != 7){
        fputs("usage: ./myclient <servn> <servaddr.conf> <mtu> <winsz> <in file path> <out file path>\n",stderr);
        exit(EXIT_FAILURE);
    }

    
    char inpath[MAXLINE+1],ip[MAXLINE+1],outpath[MAXLINE+1];
    

    struct ip_port ip_port;
    unsigned int servn = atoi(argv[1]);
    serv_n_global = servn;
    ip_port = configure_servaddr(argv[2],servn);
    
    for(unsigned int h = 0; h<servn; h++){
        printf("ip_port.ip[%d]: %s ip_port.port[%d]: %d\n", h, ip_port.ip[h],h, ip_port.port[h]);
    }
 
    sleep(3);
    unsigned int mtu = atoi(argv[3]);
    unsigned int winsz = atoi(argv[4]);
    sprintf(inpath, "./%s", argv[5]);
    strcpy(outpath, argv[6]);
    
    

    struct stat st;
    stat(inpath, &st);
    unsigned int infile_size = st.st_size;

    FILE *input;
    input = fopen(inpath, "rb"); 

    
    unsigned int total_mtu = infile_size/mtu;
    unsigned int bytes_left = infile_size - total_mtu*mtu;
    unsigned int packets_to_send=0;

    if(bytes_left>0){
        packets_to_send=total_mtu+1;
    }else{
        packets_to_send=total_mtu;
    }
    // printf("total_mtu: %d\ninfile_size:%d\npackets_to_send: %d\n",total_mtu,infile_size,packets_to_send);

 
    unsigned int seg_size;
    char* contents;
    unsigned int i, j, k, len_head;
    struct arg_struct *args;
    args = (struct arg_struct*)malloc(sizeof(struct arg_struct)*servn);
    for(k=0;k<servn;k++){
        args[k].packet_arr=(char**)malloc(sizeof(char*)*packets_to_send);
        strcpy(args[k].outpath,outpath);
        args[k].packets_to_send=packets_to_send;
        args[k].port=ip_port.port[k];
        strcpy(args[k].ip,ip_port.ip[k]);
        args[k].winsz=winsz;
    }
    for(i=0;i<packets_to_send;i++){
        if(i==(packets_to_send-1)&&bytes_left>0){
            contents = (char*)malloc(bytes_left*sizeof(char));
            if((n=fread(contents, bytes_left, 1, input))<0){
                fputs("client fread error\n",stderr);
                exit(EXIT_FAILURE);
            }
            seg_size = bytes_left;
            
        }else{
            contents = (char*)malloc(mtu*sizeof(char));
            if((n=fread(contents, mtu, 1, input))<0){
                fputs("client fread error\n",stderr);
                exit(EXIT_FAILURE);
            }
            seg_size = mtu;
        }
        char* head_data = (char*)malloc(sizeof(char)*(MAXLINE+1));
        sprintf(head_data,"%d/%d/%d/%s\n", i, seg_size, packets_to_send, outpath);
        len_head = strlen(head_data);
        for(k=0;k<servn;k++){
            args[k].packet_arr[i]=(char*)malloc(sizeof(char)*MAXLINE+1);
            for(j = 0; j < seg_size+len_head; j++){
                if(j<len_head){
                    args[k].packet_arr[i][j]=head_data[j];
                }else{
                    args[k].packet_arr[i][j]=contents[j-len_head];
                }
                
            }
            // printf("args[%d].packet_arr[%d]: %s\n",k,i,args[k].packet_arr[i]);
        }
        
   
        free(contents);

    }

        

    fclose(input);



    pthread_t thread_arr[servn];
    printf("threading now\n");
    pthread_mutex_init(&mutex, NULL);
    for(k=0;k<servn;k++){
        if (pthread_create(&thread_arr[k], NULL, &dg_cli, (void*)&args[k])!=0){
            fputs("pthread_create error\n",stderr);
            exit(EXIT_FAILURE);
            return 1;
        }
    
    }
    for(k=0;k<servn;k++){
        if (pthread_join(thread_arr[k],NULL)!=0){
            fputs("pthread_join error\n",stderr);
            exit(EXIT_FAILURE);
            return 2;
        }
    
    }
    printf("line 342\n");
    
    if(total_servers_down>=serv_n_global){
        exit(EXIT_FAILURE);
    }
    pthread_mutex_destroy(&mutex);
    exit(0);

    return 0;
}


