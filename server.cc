/*
    @project: OXCON
    @author: HSAY04
    @type: server
*/
#include <iostream>
// socket dependencies
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

/*
    @port: referencing to the ports of raspberry pico
            to send data between e
*/

#define _TXP1 21
#define _TXP2 22
#define _TXP3 24
#define _TXP4 25

#define HIGH true
#define LOW false

#define UUID char*

typedef struct _msgHeader{
    UUID senderID_;
    UUID recieverID;
}_msgHeader;

typedef struct _msg{
    _msgHeader headChunk;
    const char* _msg;
    _msgHeader endChunk;

}_msg;


bool setVAL(bool a){
    return a?1:0;
}

void _parse(_msg msg){

}

int main(){

    std::cout << setVAL(HIGH) << std::endl;
    std::cout << setVAL(LOW) << std::endl;
    
    
    return 0;
}