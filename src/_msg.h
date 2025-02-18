#pragma once

#define UUID std::string
#include <iomanip>
#include <iostream>
#include "utils.h"
const char* types[] = {"Basic","Bearer","Digest","HOBA","Mutual"};
                    //base64   OAuth2.0 sha256
char* type;
char* creds;


struct _msg{
    struct _mhead{
        UUID sendr;
        UUID recvr;
    } _head;
    std::string msgData; 
};

_msg t;

size_t size = sizeof(_msg) + sizeof(t._head) + sizeof(t.msgData);
