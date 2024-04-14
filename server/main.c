#include "interface.h"
#include "serverData.h"

int main(){
    int sd;
    struct sockaddr_in addr;

    init(&sd, &addr);

    acceptLoop(sd);

    return 0;
}