#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

int main()
{
    int client, n;
    char filename[100];
    char buffer[1024];
    pid_t pid;
    struct sockaddr_in address;

    client = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(5000);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client, (struct sockaddr *)&address, sizeof(address));

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);

    send(client, filename, strlen(filename), 0);

    recv(client, &pid, sizeof(pid), 0);

    printf("PID: %d\n", pid);

    while ((n = recv(client, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    close(client);

    return 0;
}