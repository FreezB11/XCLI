#pragma once

#define UUID char
#include <iomanip>
#include <iostream>
#include "utils.h"
const char* types[] = {"Basic","Bearer","Digest","HOBA","Mutual"};
                    //base64   OAuth2.0 sha256
char* type;
char* creds;

struct _msg{
    struct _mhead{
        UUID sendr[37];
        UUID recvr[37];
    } _head;
    char msgData[256]; 
};

struct _file{
    UUID sendr[37];
    char filecontent[1024];
};

_msg t;

size_t size = sizeof(_msg) + sizeof(t._head) + sizeof(t.msgData);
