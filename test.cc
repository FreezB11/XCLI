#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
/*
    @port: referencing to the ports of raspberry pico
            to send data between e
*/
// #define _TXP1 21
// #define _TXP2 22
// #define _TXP3 24
// #define _TXP4 25

// #define HIGH true
// #define LOW false
// bool setVAL(bool a){
//     return a?1:0;
// }

int main() {
    const char* server_ip = "";  // Replace with your server's public IP
    int server_port = 6900;  // Replace with your server's port (e.g., 80 for HTTP)

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket!" << std::endl;
        return 1;
    }

    // Define the server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported!" << std::endl;
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        return 1;
    }

    std::cout << "Connected to the server successfully!" << std::endl;

    // Send a simple HTTP GET request (optional, adjust for your use case)
    const char* message = "GET / HTTP/1.1\r\nHost: your_server_public_ip\r\n\r\n";
    send(sock, message, strlen(message), 0);
    std::cout << "HTTP request sent" << std::endl;

    // Receive response from the server
    char buffer[4096] = {0};
    int valread = read(sock, buffer, sizeof(buffer));
    std::cout << "Server response: " << buffer << std::endl;

    // Close the socket
    close(sock);

    return 0;
}
