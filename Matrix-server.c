/*
Write a TCP client-server program in C for the following: The client inputs 
an integer N and accepts the elements of a square matrix of order N × N 
from the user. The client sends the matrix to the server using TCP. The 
server analyzes the received matrix and determines whether it is an upper
triangular matrix, lower triangular matrix, diagonal matrix, or none of 
these. The server sends the identified matrix type as a string back to the 
client, which then displays the result.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server;

    int n, i, j;
    int matrix[10][10];
    char result[30];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 1);

    printf("Waiting for client...\n");

    client_fd = accept(server_fd, NULL, NULL);

    recv(client_fd, &n, sizeof(n), 0);
    recv(client_fd, matrix, sizeof(matrix), 0);

    int upper = 1, lower = 1, diagonal = 1;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {

            if(i > j && matrix[i][j] != 0)
                upper = 0;

            if(i < j && matrix[i][j] != 0)
                lower = 0;

            if(i != j && matrix[i][j] != 0)
                diagonal = 0;
        }
    }

    if(diagonal)
        strcpy(result, "Diagonal Matrix");
    else if(upper)
        strcpy(result, "Upper Triangular Matrix");
    else if(lower)
        strcpy(result, "Lower Triangular Matrix");
    else
        strcpy(result, "None");

    send(client_fd, result, sizeof(result), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}