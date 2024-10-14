#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unordered_map>
#include <thread>

std::unordered_map<std::string, int> user_sockets;  // Maps user IDs to their socket file descriptors

// Function to handle communication with a client
void handle_client(int client_socket, const std::string& user_id) {
    char buffer[1024] = {0};
    
    while (true) {
        memset(buffer, 0, sizeof(buffer));  // Clear buffer
        int valread = read(client_socket, buffer, 1024);
        if (valread <= 0) {
            std::cout << "User " << user_id << " disconnected!" << std::endl;
            user_sockets.erase(user_id);  // Remove the user from the map
            close(client_socket);
            break;
        }

        std::cout << user_id << ": " << buffer << std::endl;

        // Parse the message as "recipient message"
        std::string message(buffer);
        std::string recipient, actual_message;
        size_t space_pos = message.find(' ');
        
        if (space_pos != std::string::npos) {
            recipient = message.substr(0, space_pos);
            actual_message = message.substr(space_pos + 1);
        }

        // Send the message to the recipient if they are connected
        if (user_sockets.find(recipient) != user_sockets.end()) {
            int recipient_socket = user_sockets[recipient];
            send(recipient_socket, actual_message.c_str(), actual_message.length(), 0);
        } else {
            std::string error_msg = "Recipient not found or offline!";
            send(client_socket, error_msg.c_str(), error_msg.length(), 0);
        }
    }
}

int main() {
    int server_fd;
    sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    const int port = 6900;

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    // Define the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        return -1;
    }
    std::cout << "Server is bound to port " << port << std::endl;

    // Listen for incoming connections
    if (listen(server_fd, 10) < 0) {  // Allows up to 10 clients
        std::cerr << "Listen failed!" << std::endl;
        return -1;
    }
    std::cout << "Waiting for incoming connections..." << std::endl;

    // Accept and handle multiple clients
    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
        if (new_socket < 0) {
            std::cerr << "Accept failed!" << std::endl;
            continue;
        }

        // Receive user ID from the client
        char user_id[100] = {0};
        read(new_socket, user_id, 100);  // Assuming user_id is sent initially after connecting

        // Map the user ID to the socket
        std::string user(user_id);
        user_sockets[user] = new_socket;

        std::cout << "User " << user << " connected!" << std::endl;

        // Start a new thread to handle this client's communication
        std::thread client_thread(handle_client, new_socket, user);
        client_thread.detach();  // Detach the thread so it can run independently
    }

    close(server_fd);
    return 0;
}
