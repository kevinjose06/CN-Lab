/*Implement a concurrent Time Server application using UDP to execute the program at a
remote server. The client sends a time request to the server which sends its system time
back. The client then displays the received time value.*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int sock;

struct client
{
    struct sockaddr_in address;
    socklen_t length;
};

void *send_time(void *arg)
{
    struct client *c = (struct client *)arg;
    char buffer[100];

    time_t t = time(NULL);

    strcpy(buffer, ctime(&t));

    sendto(sock, buffer, strlen(buffer), 0,
           (struct sockaddr *)&c->address, c->length);

    free(c);

    return NULL;
}

int main()
{
    struct sockaddr_in server, client;
    socklen_t length;
    char request[100];
    pthread_t thread;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Time Server Started...\n");

    while (1)
    {
        length = sizeof(client);
        recvfrom(sock, request, sizeof(request), 0,
                 (struct sockaddr *)&client, &length);

        printf("Request received\n");

        struct client *c = malloc(sizeof(struct client));

        c->address = client;
        c->length = length;
        pthread_create(&thread, NULL, send_time, c);

        pthread_detach(thread);
    }

    close(sock);

    return 0;
}