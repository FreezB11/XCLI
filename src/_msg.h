#pragma once

#define UUID const char*
#include <iomanip>
#include <iostream>
#include "utils.h"
const char* types[] = {"Basic","Bearer","Digest","HOBA","Mutual"};
                    //base64   OAuth2.0 sha256
char* type;
char* creds;

template <typename T>
struct _msgHeader
{ 
    UUID _sender;
    UUID _reciever;
    //Date
    //const char* date = tlog(" ");
    //Authorization <type> <credentials>
    //std::pair<type, creds> Auth;
    //Message type
    char* msgType;
    //Encryption type
    char* _encryptionType;

};

template <typename T>
struct _msg{
    _msgHeader<T> head;
    T msgData; 
};
