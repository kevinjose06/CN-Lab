#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int client;

void *receive(void *arg)
{
    char msg[1024];
    int n;

    while (1)
    {
        n = recv(client, msg, sizeof(msg), 0);

        if (n <= 0)
            break;

        msg[n] = '\0';

        printf("\n%s", msg);
    }

    return NULL;
}

int main()
{
    struct sockaddr_in server;
    char msg[1024];
    pthread_t thread;

    client = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client, (struct sockaddr *)&server, sizeof(server));
    printf("Connected to server\n");
    pthread_create(&thread, NULL, receive, NULL);

    while (1)
    {
        printf("You: ");
        fgets(msg, sizeof(msg), stdin);

        if (strncmp(msg, "exit", 4) == 0)
            break;

        send(client, msg, strlen(msg), 0);
    }

    close(client);

    return 0;
}