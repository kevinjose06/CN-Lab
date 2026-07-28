/*
Write a TCP client-server program in C where the client sends a message to 
the server, and the server receives and displays the message.
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server;
    char buffer[100];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 1);

    printf("Waiting for client...\n");

    client_fd = accept(server_fd, NULL, NULL);

    recv(client_fd, buffer, sizeof(buffer), 0);

    printf("Message from client: %s\n", buffer);

    close(client_fd);
    close(server_fd);

    return 0;
}