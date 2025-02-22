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
    io::log<INFO>("initializing server");
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

void XSRV::xreg(std::string uuid, std::string pub_key){
    if(!std::filesystem::exists("./.srv")){
        std::filesystem::create_directory("./.srv");
    }else{
        if(!std::filesystem::exists("./.srv/.user_ids")){
            std::ofstream user_data("./.srv/.user_ids");
            user_data.close();
        }
    }
    std::ofstream user_data("./.srv/.user_ids", std::ios::app);
    std::ofstream pubk("./.srv/"+uuid+"_pub.pem");
    pubk << pub_key;
    user_data << uuid << std::endl;
    user_data.close();
}

_msg server_m = {
    ._head = {
        .sendr = "nigga sent you this",
        .recvr = "pablo escobar"
    },
    .msgData = "hello from russia"
};

_msgType mrt;

int main(){
    XSRV server;

    while(true){
        server.start();
        _msg recv_msg = {};
        _file recv_file = {};
        io::log<INFO>("here");

        mrt = server.xrecv<_msgType>();
        if(mrt == msg){
             recv_msg = server.xrecv<_msg>();
             io::log<INFO>(recv_msg._head.sendr);
             io::log<INFO>(recv_msg._head.recvr);
             io::log<INFO>(recv_msg.msgData);
        }else if(mrt == file){
            recv_file = server.xrecv<_file>();
            server.xreg(recv_file.sendr, recv_file.filecontent);
            io::log<INFO>(recv_file.sendr);
            io::log<INFO>(recv_file.filecontent);
        }

        // recv_msg = server.xrecv<_msg>();

        // io::log<INFO>(recv_msg._head.sendr);
        // io::log<INFO>(recv_msg._head.recvr);
        // io::log<INFO>(recv_msg.msgData);

        server.xsend(&server_m, sizeof(server_m));
    }
    std::cout << "so we are here" << std::endl;

}