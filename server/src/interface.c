#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
//#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "interface.h"
#include "serverData.h"

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

extern UserList userList;

char quit[]="/quit";

void init(int *serv_sd, struct sockaddr_in *addr){
    memset(&userList,0,sizeof(userList));

    addr->sin_family = AF_INET;            // 인터넷 통신으로 설정
    addr->sin_port = htons(PORT);          // 포트 번호를 빅엔디안 방식으로 변환
    addr->sin_addr.s_addr = inet_addr(IP); // IP를 2진수로 변환

    if ( (*serv_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ // 소켓 생성
        perror("socket");
        exit(1);
    }

    if (bind(*serv_sd, (struct sockaddr *)addr, sizeof(struct sockaddr_in)) == -1){ // bind
        perror("bind");
        exit(1);
    }

    if (listen(*serv_sd, MAXCLIENT) == -1){ // listen
        perror("listen");
        exit(1);
    }

    printf("Waiting for clienets...\n");
}

// send to all client except received client
void sendAll(int except_cli_sd, Data *data){
    for(int i=0;i<MAXCLIENT;i++){
        if(userList.user[i].cli_sd==0 || userList.user[i].cli_sd==except_cli_sd) continue;
        if(send(userList.user[i].cli_sd, data, sizeof(Data), 0)==-1){
            perror("sendAll");
            exit(1);
        }
    }
}

void terminate(User *user){
    close(user->cli_sd);
    user->cli_sd=0;
}

void thrd_routine(User *user){
    Data data;
    int cli_sd=user->cli_sd;

    memset(&data, 0, sizeof(Data));
    strcpy(data.message, "welcome! please type user name\n");
    strcat(data.message, "name: ");
    
    // send welcom message
    if(send(cli_sd, &data, sizeof(Data), 0)==-1){
        perror("send");
        exit(1);
    }

    // receiv name
    if(recv(cli_sd, &data, sizeof(Data), 0)==-1){
        perror("recv");
        exit(1);
    }

    printf("a new client %s accessed\n", data.name);

    while(recv(cli_sd, &data, sizeof(Data),0) != -1){
        if((strcmp(data.message, quit))==0){
            userList.loggedon-=1;
            break;
        }

        printf("received message: %s\n",data.message);

        pthread_mutex_lock(&mutex);
        sendAll(cli_sd, &data);
        pthread_mutex_unlock(&mutex);
    }

    printf("client %s terminated\n", data.name);

    pthread_mutex_lock(&mutex);
    terminate(user);
    pthread_mutex_unlock(&mutex);
}

void acceptLoop(int serv_sd){
    int cli_sd;

    while ((cli_sd = accept(serv_sd, NULL, NULL)) != -1){
        User *user=getEmtpyUsrAddr();
        user->cli_sd=cli_sd;

        if(pthread_create(&(user->thread),NULL,(void *)thrd_routine, (void*)user) == -1){
            perror("pthread_create");
            exit(1);
        }
    }
}