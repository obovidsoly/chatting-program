#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <arpa/inet.h>

#include "serverData.h"

void init(int *serv_sd, struct sockaddr_in *addr);

void sendAll(int except_cli_sd, Data *data);

void terminate(User *user);

void thrd_routine(User *user);

void acceptLoop(int serv_sd);

#endif
