#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

int main()
{
    int sock;
    char buffer[65536];
    struct iphdr *ip;
    struct tcphdr *tcp;
    struct sockaddr_in source, dest;

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    if (sock < 0)
    {
        perror("Socket error");
        return 1;
    }

    printf("TCP packet capturing started...\n");

    while (1)
    {
        int n = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);

        if (n < sizeof(struct iphdr))
            continue;

        ip = (struct iphdr *)buffer;

        if (ip->version != 4)
            continue;

        if (ip->protocol != IPPROTO_TCP)
            continue;

        source.sin_addr.s_addr = ip->saddr;
        dest.sin_addr.s_addr = ip->daddr;

        if (n < ip->ihl * 4 + sizeof(struct tcphdr))
            continue;

        tcp = (struct tcphdr *)(buffer + ip->ihl * 4);

        printf("\nSource IP       : %s", inet_ntoa(source.sin_addr));
        printf("\nDestination IP  : %s", inet_ntoa(dest.sin_addr));
        printf("\nSource Port     : %d", ntohs(tcp->source));
        printf("\nDestination Port: %d\n", ntohs(tcp->dest));
    }

    close(sock);

    return 0;
}