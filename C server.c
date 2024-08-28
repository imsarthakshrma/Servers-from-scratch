#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define P 3030
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "HTTP/1.1 200 OK\r\nContedt-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World";

    // Create Socket File Descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket Failed"); 
        exit(EXIT_FAILURE);
    }

    //Defining The Address For The Sockets here.

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind The Sockets To the Address And Port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind Failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming Connections
    if(listen(server_fd, 3) < 0) {
        perror("Listen Failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while(1) {
        // Accepting incoming Connections here.
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept Failed"); 
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        // Read the incoming HTTP request
        read(new_socket, buffer, BUFFER_SIZE);

        // Sending the HTTP Response back
        printf("Response Sent\n");

        //Close the Connection with The Client
        close(new_socket);

    }

    close(server_fd);
    return 0;
}