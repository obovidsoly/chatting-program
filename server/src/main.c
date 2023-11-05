#include <arpa/inet.h>

#include "interface.h"
#include "serverData.h"

int main(){
    int serv_sd;        // 서버의 소켓 기술자와 클라이언트의 소켓 기술자
    struct sockaddr_in addr;    // 서버의 주소정보를 담을 구조체

    init(&serv_sd, &addr);

    acceptLoop(serv_sd);
}