#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

int PORT = 3389;

int main(int argc, const char **argv){
    
    int sock =0, valread;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = {};

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "Socket creation error\n";
        return -1;       
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

  
    if(inet_pton(AF_INET, "-------", &serv_addr.sin_addr) <= 0){
        std::cout << "Bad Address\n";
    }

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        std::cout << "Connection Failed\n"; 
    }

    send(sock, hello, strlen(hello), 0);
    std::cout << "Message Sent\n";

    valread = read(sock, buffer, 1024);
    std::cout << buffer << '\n';
    
    return 0;

}
