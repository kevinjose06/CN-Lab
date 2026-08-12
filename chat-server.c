// Implement a multi-user chat server using TCP as the transport layer protocol.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

int main()
{
    int server, client, clients[10] = {0};
    char msg[100];

    server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (struct sockaddr *)&addr, sizeof(addr));
    listen(server, 5);

    printf("Chat server started...\n");

    while (1)
    {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(server, &set);

        int max = server;

        for (int i = 0; i < 10; i++)
        {
            if (clients[i] > 0)
            {
                FD_SET(clients[i], &set);

                if (clients[i] > max)
                    max = clients[i];
            }
        }

        select(max + 1, &set, NULL, NULL, NULL);

        if (FD_ISSET(server, &set))
        {
            client = accept(server, NULL, NULL);

            for (int i = 0; i < 10; i++)
            {
                if (clients[i] == 0)
                {
                    clients[i] = client;
                    break;
                }
            }

            printf("New client connected\n");
        }

        for (int i = 0; i < 10; i++)
        {
            if (clients[i] > 0 && FD_ISSET(clients[i], &set))
            {
                int n = recv(clients[i], msg, sizeof(msg), 0);

                if (n <= 0)
                {
                    close(clients[i]);
                    clients[i] = 0;
                    printf("Client disconnected\n");
                }
                else
                {
                    msg[n] = '\0';

                    for (int j = 0; j < 10; j++)
                    {
                        if (clients[j] > 0)
                            send(clients[j], msg, strlen(msg), 0);
                    }
                }
            }
        }
    }

    close(server);
    return 0;
}