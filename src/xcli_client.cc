/*
    @author: hsay
    
    the main client side code..
*/
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


/*
     we shall implement a function to get the server port and ip
*/

#define TEMP_port 8080
#define TEMP_ip "127.0.0.1"

int main(int argc, char* argv[]){
    int sock = socket(AF_INET, SOCK_STREAM, 0);

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

    send(sock, msg, strlen(msg), 0);
    recv(sock, (void *)reply, sizeof(reply), 0);
    std::cout << reply << std::endl;
    close(sock);
}