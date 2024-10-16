/* 
    @author: hsay
    the main server code
*/
#include <iostream>
//socket deps
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define TEMP_port 8080

int main(){
    int client_sock[5];
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    const char* msg;


    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(TEMP_port);

    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    char buffer[1024] = {0};
    int i = 0;
    while(true){
        listen(server_sock, 5);
        client_sock[i] = accept(server_sock, nullptr, nullptr);
        if(recv(client_sock[i], buffer, sizeof(buffer),0) > 0 ){
            std::cout << buffer << std::endl;
            i++;
        }else{
            break;
        }
    }
    std::cout << "so we are here" << std::endl;

}