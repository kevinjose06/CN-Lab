#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock;
    char msg[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Connected to chat server\n");

    while (1)
    {
        printf("Enter message: ");
        fgets(msg, sizeof(msg), stdin);

        send(sock, msg, strlen(msg), 0);

        int n = recv(sock, msg, sizeof(msg), 0);

        msg[n] = '\0';

        printf("Message: %s", msg);
    }

    close(sock);
    return 0;
}