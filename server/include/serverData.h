#ifndef _SERVER_DATA_H
#define _SERVER_DATA_H

#include <pthread.h>

#define MAXCLIENT 20000

#define IP "127.0.0.1"
#define PORT 1234


typedef struct{
    char message[256];
    char name[20];
} Data;


typedef struct {
    char name[20];
    int cli_sd;             // 0: empty
    pthread_t thread;
} User;


typedef struct {
    User user[MAXCLIENT];
    unsigned int loggedon;
} UserList;

User* getEmtpyUsrAddr();

#endif