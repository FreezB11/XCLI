/*
    @author: hsay
    
    the main client side code..
*/
#include <iostream>
#include "xcli.h"
#include "_msg.h"
#include <string.h>

XCLI::XCLI(){
    init();
}

void XCLI::init(){
    this->cli_s = socket(AF_INET, SOCK_STREAM, 0);
    this->serv_a.sin_family = AF_INET;
    this->serv_a.sin_port = htons(PORT);
    if(inet_pton(AF_INET, TEMP_ip, &this->serv_a.sin_addr) <= 0){
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return;
    }
}

void XCLI::start(){
    if(connect(this->cli_s,(struct sockaddr*)&this->serv_a,sizeof(this->serv_a)) < 0){
        std::cerr << "connection failed" << std::endl;
        return;
    }
}

void XCLI::xsend(const void *__buf, size_t __n, int __flags = 0){
    send(this->cli_s, __buf, __n, __flags);
}

template<typename T>
T XCLI::xrecv(){
    T t;
    recv(this->cli_s, &t, sizeof(t),0);
    return t;
} 

XCLI::~XCLI(){
    close(this->cli_s);
}

int main(int argc, char* argv[]){
    XCLI cli;
    cli.start();

    _msg test ={
        ._head = {
            .sendr = "yash",
            .recvr = "yash2",
        },
        .msgData = "test",
    };

    cli.xsend(&test, sizeof(test));

    _msg recv_msg = {};
    recv_msg = cli.xrecv<_msg>();
    log(recv_msg._head.sendr)
    log(recv_msg._head.recvr)
    log(recv_msg.msgData)
}
