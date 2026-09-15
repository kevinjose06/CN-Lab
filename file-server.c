/*Develop a concurrent file server that will provide the file requested by the client if it
exists. If not, the server sends an appropriate message to the client. The server should also
send its process ID (PID) to clients for displaying along with the file contents or with the
message.*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int server, client, fd, n;
    char filename[100];
    char buffer[1024];
    char message[1200];
    struct sockaddr_in address;
    pid_t pid;

    server = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    bind(server, (struct sockaddr *)&address, sizeof(address));
    listen(server, 5);

    printf("Server started...\n");

    while (1)
    {
        client = accept(server, NULL, NULL);

        pid = fork();

        if (pid == 0)
        {
            close(server);

            recv(client, filename, sizeof(filename) - 1, 0);
            filename[strcspn(filename, "\n")] = '\0';

            fd = open(filename, O_RDONLY);

            if (fd < 0)
            {
                sprintf(message, "PID: %d\nFile not found\n", getpid());
                send(client, message, strlen(message), 0);
            }
            else
            {
                sprintf(message, "PID: %d\n", getpid());
                send(client, message, strlen(message), 0);

                while ((n = read(fd, buffer, sizeof(buffer))) > 0)
                    send(client, buffer, n, 0);

                close(fd);
            }

            close(client);
            return 0;
        }

        close(client);
    }

    return 0;
}