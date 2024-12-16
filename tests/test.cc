#include <iostream>

int main()
{
    char* msg = "The backlog parameter is not a maximum number of connections allowed parameter. Rather its just a hint to the stack about how many TCP connections can be accepted on the sockets port before the applicaiton code has invoked accept on that socket. Be aware that accept doesnt negotiate a TCP handshake, it just takes one of the already accepted connections out of the backlog queue (or waits for one to arrive).";
    std::cout << msg << std::endl;
    void* m2 = (void*)msg;
    std::cout << m2 << std::endl;
    char* m3 = (char*)m2;
    std::cout << m3 << std::endl;
    return 0;
}