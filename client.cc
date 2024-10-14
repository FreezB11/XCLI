#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <user_id>" << std::endl;
        return 1;
    }

    const char* server_ip = "";  // Replace with your server's public IP
    int server_port = 6900;

    // Extract command-line argument for user_id
    std::string user_id = argv[1];

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket!" << std::endl;
        return 1;
    }

    // Define server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    // Convert IP address to binary form
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

    // Send the user ID to the server
    send(sock, user_id.c_str(), user_id.length(), 0);

    // Enter a loop to send messages continuously
    while (true) {
        std::string recipient_id;
        std::string message;

        std::cout << "Enter recipient ID: ";
        std::getline(std::cin, recipient_id);

        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        if (recipient_id == "exit" || message == "exit") {
            std::cout << "Exiting chat." << std::endl;
            break;
        }

        // Combine recipient ID and message into one string
        std::string full_message = recipient_id + " " + message;

        // Send message to the server
        send(sock, full_message.c_str(), full_message.length(), 0);

        // Wait for server's response (if any)
        char buffer[1024] = {0};
        int valread = read(sock, buffer, 1024);
        if (valread > 0) {
            std::cout << "Server: " << buffer << std::endl;
        }
    }

    // Close the socket
    close(sock);

    return 0;
}
