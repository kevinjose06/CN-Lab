#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;

    int n, i, j;
    int matrix[10][10];
    char result[30];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Enter order of matrix: ");
    scanf("%d", &n);

    printf("Enter matrix elements:\n");

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    send(sock, &n, sizeof(n), 0);
    send(sock, matrix, sizeof(matrix), 0);

    recv(sock, result, sizeof(result), 0);

    printf("Matrix Type: %s\n", result);

    close(sock);

    return 0;
}