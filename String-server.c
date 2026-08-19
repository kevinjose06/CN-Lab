/*
Client-Server communication using UDP:- You are very good at communicating in the
“new generation” English language with all sorts of abbreviations like tbh, ig, etc. Now
design a client-server application as follows: The client inputs a new-generation English
sentence from the user and sends it to the server. The server then translates the received
sentence to formal English and sends the translated sentence back to the client which it
prints.
Sample string sent to the server
Really idc about this stupid server as it is of no use irl but atm, I will design one, tbf to the
professor.
Translated string sent back to the client
Really I don't care about this stupid server as it is of no use in real life but at the moment, I
will design one, to be fair to the professor.
You may consider only the following abbreviations: tbh, ig, tbf, atm, irl, lol, asap, omg,
ttyl, idk, nvm
*/

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t len = sizeof(clientAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    printf("UDP Server Running...\n");

    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&clientAddr, &len);

    printf("Received: %s\n", buffer);

    char *abbr[] = {"idc","tbh","ig","tbf","atm","irl","lol","asap","omg","ttyl","idk","nvm"};
    char *full[] = {"I don't care","to be honest","I guess","to be fair","at the moment","in real life","laughing out loud",
    "as soon as possible","oh my God","talk to you later","I don't know","never mind";

    char result[1024] = "";
    char *word = strtok(buffer, " ");

    while (word != NULL) {
        int found = 0;

        for (int i = 0; i < 11; i++) {
            if (strcmp(word, abbr[i]) == 0) {
                strcat(result, full[i]);
                found = 1;
                break;
            }
        }

        if (!found)
            strcat(result, word);

        strcat(result, " ");
        word = strtok(NULL, " ");
    }
    sendto(sockfd, result, strlen(result) + 1, 0,
           (struct sockaddr *)&clientAddr, len);

    printf("Translated sentence sent.\n");

    return 0;
}