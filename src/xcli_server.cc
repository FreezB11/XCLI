/* 
    @author: hsay
    the main server code
*/
#include <iostream>
#include "xcli.h"
#include "_msg.h"

struct ttm{
    int id;
    char dat[256];
};

XSRV::XSRV(){
    init();
}

void XSRV::init(){
    this->sockn = socket(AF_INET, SOCK_STREAM, 0);
    this->serv_a.sin_family = AF_INET;
    this->serv_a.sin_addr.s_addr = INADDR_ANY;
    this->serv_a.sin_port = htons(PORT);
    bind(this->sockn, (struct sockaddr*)&this->serv_a, sizeof(this->serv_a));
}

void XSRV::start(){
    listen(this->sockn, 10);
    this->cli_s = accept(this->sockn, nullptr, nullptr);
}

template<typename T>
T XSRV::xrecv(){
    T t;
    recv(this->cli_s, &t, sizeof(t),0);
    return t;
}   

void XSRV::xsend(const void *__buf, size_t __n, int __flags = 0){
    send(this->cli_s, __buf, __n,__flags);
}

int main(){

    XSRV server;
    char reply[1024] = "reply from server";

    while(true){
        server.start();
        _msg recv_msg = {};
        log("here")
        // recv(client_sock, &recvv, sizeof(recvv),0);
        recv_msg = server.xrecv<_msg>();
       
        // if(!recv(client_sock, &recv_msg, size,0)){
        //     log("here")
        //     log("fuck off this code doesnt work nigga")
            
        // };
        log(recv_msg._head.sendr)
        log(recv_msg._head.recvr)
        log(recv_msg.msgData)
        // send(client_sock, reply, sizeof(reply),0);
        server.xsend(reply, sizeof(reply));
    }
    std::cout << "so we are here" << std::endl;

}