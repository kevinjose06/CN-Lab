// Implement a multi-user chat server using TCP as the transport layer protocol.


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX 10

int clients[MAX];
int client_id[MAX];
int count = 0;
int next_id = 1;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg)
{
    int client = *(int *)arg;
    free(arg);

    char msg[1024];
    char message[1100];
    int n, i, id = 0;

    pthread_mutex_lock(&lock);

    for (i = 0; i < count; i++)
    {
        if (clients[i] == client)
        {
            id = client_id[i];
            break;
        }
    }

    pthread_mutex_unlock(&lock);

    while (1)
    {
        n = recv(client, msg, sizeof(msg) - 1, 0);

        if (n <= 0)
            break;

        msg[n] = '\0';

        snprintf(message, sizeof(message), "Client %d: %s", id, msg);

        pthread_mutex_lock(&lock);

        for (i = 0; i < count; i++)
        {
            if (clients[i] != client)
            {
                send(clients[i], message, strlen(message), 0);
            }
        }

        pthread_mutex_unlock(&lock);
    }

    pthread_mutex_lock(&lock);

    for (i = 0; i < count; i++)
    {
        if (clients[i] == client)
        {
            clients[i] = clients[count - 1];
            client_id[i] = client_id[count - 1];
            count--;
            break;
        }
    }

    pthread_mutex_unlock(&lock);

    close(client);

    printf("Client %d disconnected\n", id);

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

        if (client < 0)
            continue;

        pthread_mutex_lock(&lock);

        if (count == MAX)
        {
            pthread_mutex_unlock(&lock);
            close(client);
            continue;
        }

        clients[count] = client;
        client_id[count] = next_id++;

        printf("Client %d connected\n", client_id[count]);

        count++;

        pthread_mutex_unlock(&lock);

        int *p = malloc(sizeof(int));
        *p = client;

        pthread_create(&thread, NULL, handle_client, p);
        pthread_detach(thread);
    }

    close(server);

    return 0;
}
