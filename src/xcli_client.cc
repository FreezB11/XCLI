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


int main(int argc, char *argv[]){

    XCLI cli;
    cli.start();

    // umm the user shall register first
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " -r <user_name> | -s <user_name> <msg> | -l | -h" << std::endl;
        return 1;
    }

    std::string option = argv[1];

    if (option == "-r") {
        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " -r <user_name>" << std::endl;
            return 1;
        }
        std::string user_name = argv[2];
        // Register the user
        cli._registr();
        return 0;
    } else if (option == "-s") {
        if (argc != 4) {
            std::cerr << "Usage: " << argv[0] << " -s <user_name> <msg>" << std::endl;
            return 1;
        }

        _msg test ;
        strcpy(test._head.sendr, argv[2]);
        strcpy(test._head.recvr, "server");
        strcpy(test.msgData, argv[3]);

        cli.xsend(&test, sizeof(test));
        return 0;
    } else if (option == "-h") {
        std::cout << "Usage: " << argv[0] << " -r <user_name> | -s <user_name> <msg> | -h" << std::endl;
        std::cout << "i didnt pass anything so this will go" << std::endl;
    cli.xsecure();
        return 0;
    } else {
        std::cerr << "Invalid option" << std::endl;
        return 1;
    }
    return 0;
}
