#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

#include <sys/ioctl.h>

#include "clientData.h"

#define IP "127.0.0.1" // 서버의 임시 IP
#define PORT 1234      // 서버의 포트 번호

int sd;
void (*handler)(int);

void terminate(){
    close(sd);
    exit(0);
}


void sigTermHandler(int signo){
    terminate();
}


// connect to server
void init(int *sd, struct sockaddr_in *addr){
    addr->sin_family = AF_INET; // 서버 주소 변환
    addr->sin_port = htons(PORT);
    addr->sin_addr.s_addr = inet_addr(IP);

    handler=signal(SIGTERM, sigTermHandler);
    if(handler==SIG_ERR){
        perror("signal");
        exit(1);
    }

    if ((*sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // 소켓 생성
        perror("socket");
        exit(1);
    }

    printf("connecting...\n");
    if (connect(*sd, (struct sockaddr *)addr, sizeof(struct sockaddr_in)) == -1){ // 서버에 연결
        perror("connect");
        exit(1);
    }
}


int main(void)
{
    struct sockaddr_in addr;
    pid_t pid;
    char quit[] = "/quit";
    char name[20];
    Data data;
    
    init(&sd, &addr);

    // receive welcome message
    if(recv(sd, &data, sizeof(Data), 0) == -1){
        perror("recv");
        exit(1);
    }

    printf("%s", data.message);

    // input name from console
    if (fgets(name, sizeof(name), stdin) == NULL){
        perror("fgets");
        exit(1);
    }

    name[strlen(name)-1]='\0';
    strcpy(data.name, name);

    // send name
    if(send(sd, &data, sizeof(Data), 0) ==-1){
        perror("send");
        exit(1);
    }

    printf("\nSuccessfully Accessed\n\n");

    

    switch (pid = fork()){
    case -1:
        perror("fork");
        exit(1);
        break;

    // child process
    // Rx only
    case 0:
        while(recv(sd, &data, sizeof(Data), 0) != -1){
            printf("%s: %s\n", data.name, data.message);
        }

        break;

    // parent process
    // Tx only
    default:
        strcpy(data.message, name);

        while(1) {
            if (fgets(data.message, sizeof(data.message), stdin) == NULL){
                perror("fgets");
                exit(1);
            }

            if(strcmp(data.message, "\n") == 0) continue;
            data.message[strlen(data.message)-1]='\0';

            if(send(sd, &data, sizeof(Data), 0) == -1){
                perror("send");
                exit(1);
            }

            if(strcmp(data.message,quit) == 0){
                kill(pid, SIGTERM);
                break;
            }
        }
    }

    if(wait(NULL) == (pid_t)-1){
        perror("wait");
        exit(1);
    }

    terminate(sd);
}