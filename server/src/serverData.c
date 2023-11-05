#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <pthread.h>

#include "serverData.h"

UserList userList;

User* getEmtpyUsrAddr(){
    User *cli_addr=NULL;

    for(int i=0;i<MAXCLIENT;i++){
        if(userList.user[i].cli_sd != 0) continue;
        cli_addr=&(userList.user[i]);
        break;
    }

    return cli_addr;
}