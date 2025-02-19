#pragma once
#include "utils.h"
#include "log.hh"
#include <string>
#include "xrsa.h"
#include <netinet/in.h>

//socket deps
#define _XOPEN_SOURCE_EXTENDED 1
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 2104
#define TEMP_ip "127.0.0.1"

typedef char UUID[37];

UUID* gen_uuid();

class X{
protected:
    sockaddr_in serv_a;
/*
    umm the here the send and recv func should be made
    and also 
    syn
    ack
    and syn&ack
*/
};

class XCLI : public X{
public:
    XCLI();
    ~XCLI();
    void start();
    void xsend(const void *__buf, size_t __n, int __flags);
    template<typename T>
    T xrecv();
    void _registr();
private:
    void init();
    void xsecure();
    int cli_s;
};

class XSRV : public X{
public:
    XSRV();    
    void start();
    template<typename T>
    T xrecv();
    // send(int __fd, const void *__buf, size_t __n, int __flags)
    void xsend(const void *__buf, size_t __n, int __flags);
private:
    int sockn;
    int cli_s;
    void init();
};