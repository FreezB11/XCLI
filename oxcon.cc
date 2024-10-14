/*
    @project: OXCON
    @author: HSAY04
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



void _parse(_msg msg){

}

int main(int argc, char* argv[]){


    

    return 0;
}