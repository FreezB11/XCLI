#pragma once

#define UUID const char*
#include <iomanip>
#include <iostream>
#include "utils.h"
const char* types[] = {"Basic","Bearer","Digest","HOBA","Mutual"};
                    //base64   OAuth2.0 sha256
char* type;
char* creds;


struct _msgHeader
{ 
    UUID _sender = nullptr;
    UUID _reciever = nullptr;
    //Date
    //const char* date = tlog(" ");
    //Authorization <type> <credentials>
    //std::pair<type, creds> Auth;
    //Message type
    const char* msgType = nullptr;
    //Encryption type
    const char* _encryptionType = nullptr;

};

struct _msg{
    _msgHeader *head = nullptr;
    std::string msgData; 
};
