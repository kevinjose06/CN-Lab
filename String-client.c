#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() 
{
    int sockfd;
    char buffer[1024];

    struct sockaddr_in serverAddr;
    socklen_t len = sizeof(serverAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter sentence:\n");
    fgets(buffer, sizeof(buffer), stdin);

    buffer[strcspn(buffer, "\n")] = '\0';

    sendto(sockfd, buffer, strlen(buffer) + 1, 0,
           (struct sockaddr *)&serverAddr, len);

    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&serverAddr, &len);

    printf("\nTranslated Sentence:\n%s\n", buffer);

    return 0;
}