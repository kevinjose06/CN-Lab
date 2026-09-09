// Implement a multi-user chat server using TCP as the transport layer protocol.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 10

int clients[MAX];
int count = 0;

void *handle_client(void *arg)
{
    int client = *(int *)arg;
    int id = 0;
    char msg[1024];
    char message[1100];
    int i, n;

    for (i = 0; i < count; i++)
    {
        if (clients[i] == client)
        {
            id = i + 1;
            break;
        }
    }
    while (1)
    {
        n = recv(client, msg, sizeof(msg) - 1, 0);

        if (n <= 0)
            break;

        msg[n] = '\0';
        for (i = 0; i < count; i++)
        {
            if (clients[i] != client)
                send(clients[i], message, strlen(message), 0);
        }
    }

    close(client);
    return NULL;
}

int main()
{
    int server, client;
    struct sockaddr_in address;
    pthread_t thread;

    server = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    bind(server, (struct sockaddr *)&address, sizeof(address));
    listen(server, MAX);

    printf("Server started...\n");

    while (1)
    {
        client = accept(server, NULL, NULL);

        clients[count] = client;
        count++;

        printf("Client %d connected\n", count);

        pthread_create(&thread, NULL, handle_client, &client);
    }

    return 0;
}