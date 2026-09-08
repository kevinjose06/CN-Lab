#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock;
    char request[] = "TIME";
    char buffer[100];

    struct sockaddr_in server;
    socklen_t length = sizeof(server);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send request
    sendto(sock, request, strlen(request), 0,
           (struct sockaddr *)&server, sizeof(server));

    // Receive time
    recvfrom(sock, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server, &length);

    printf("Server Time: %s", buffer);

    close(sock);

    return 0;
}