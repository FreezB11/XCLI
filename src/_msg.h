#pragma once

#define UUID const char*


const char* types[] = {"Basic","Bearer","Digest","HOBA","Mutual"};
                    //base64   OAuth2.0 sha256  
template <typename T>
struct _msgHeader
{ 
    UUID _sender;
    UUID _reciever;
    //Date 
    //Authorization <type> <credentials>
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