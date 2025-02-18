/*
    @author: hsay
    
    the main client side code..
*/
#include <iostream>
#include <cstring>
#define _XOPEN_SOURCE_EXTENDED 1
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "_msg.h"

/*
     we shall implement a function to get the server port and ip
*/

struct ttm{
    int id;
    std::string dat;
};

#define TEMP_port 8080
#define TEMP_ip "127.0.0.1"

int main(int argc, char* argv[]){
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct _msg test_msg;
    // test_msg.head._sender = "i am the sender";
    // test_msg.head._reciever = " nigga is the reciever";
    // test_msg.head.msgType = "char";
    // test_msg.head._encryptionType = "SHA-256";
    test_msg.msgData = "hey this the test msg from the msg block";

    const char* msg = argv[1];
    const char reply[1024] = {0};
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TEMP_port);

    //convert the ip to binary form 
    if(inet_pton(AF_INET, TEMP_ip, &server_addr.sin_addr) <= 0){
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return 1;
    }

    if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        std::cerr << "connection failed" << std::endl;
        return 1;
    }
    _msg test ={
        ._head = {
            .sendr = "yash",
            .recvr = "yash2",
        },
        .msgData = "test",
    };

    ttm testm = {
        .id = 8,
        .dat = "hello",
    };

    send(sock, &testm, sizeof(testm),0);
    // send(sock, &test._head, sizeof(test._head), 0);
    recv(sock, (void *)reply, sizeof(reply), 0);
    std::cout << reply << std::endl;
    close(sock);
}
