/*
    @author: hsay
    
    the main client side code..
*/
#include <iostream>
#include "xrsa.h"
#include "xcli.h"
#include "_msg.h"
#include <string.h>
#include <fstream>
#include <filesystem>

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

void XCLI::xsecure(){
    // secure the connection
    GEN_RSA_KEY("priv.pem", "pub.pem");
    // send the public key to the server
    std::ifstream pubFile("pub.pem");
    std::string pubKey((std::istreambuf_iterator<char>(pubFile)), std::istreambuf_iterator<char>());    
    xsend(pubKey.c_str(), pubKey.size());
}

void XCLI::_registr(){
    if(std::filesystem::exists(".xcli")){
        io::log<INFO>("User already registered");
        return;
    }else{
        io::log<INFO>("Registering the user");
        std::ofstream iuser(".xcli");
        if(!iuser.is_open()){
            io::log<ERROR>("User file not found");
            return;
        }
        char uuid[37] = {0};
        generate_uuidv7(uuid);
        std::string uuid_str(uuid);
        iuser << uuid << std::endl;
        GEN_RSA_KEY(uuid_str +"_priv"+".pem", uuid_str +"_pub"+".pem");
        iuser.close();
    }

}


int main(){
    XCLI cli;
    cli._registr();
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
    io::log<INFO>(recv_msg._head.sendr);
    io::log<INFO>(recv_msg._head.recvr);
    io::log<INFO>(recv_msg.msgData);
}
