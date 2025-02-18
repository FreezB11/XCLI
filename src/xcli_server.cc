/* 
    @author: hsay
    the main server code
*/
#include <iostream>
//socket deps
#define _XOPEN_SOURCE_EXTENDED 1
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#include "_msg.h"

struct ttm{
    int id;
    std::string dat;
};

#define TEMP_port 8080

int main(){
    int client_sock;
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    const char* msg;


    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(TEMP_port);

    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char reply[1024] = "reply from server";

    while(true){
        listen(server_sock, 10);
        log("here")
        client_sock = accept(server_sock, nullptr, nullptr);
        _msg recv_msg = {};
        log("here")
        ttm recvv;
        recv(client_sock, &recvv, sizeof(recvv),0);
        // recv(client_sock, &recv_msg._head, sizeof(recv_msg._head),0);
       
        // if(!recv(client_sock, &recv_msg, size,0)){
        //     log("here")
        //     log("fuck off this code doesnt work nigga")
            
        // };
        log(recvv.id)
        log(recvv.dat)
        send(client_sock, reply, sizeof(reply),0);
    }
    std::cout << "so we are here" << std::endl;

}