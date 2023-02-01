/*
** EPITECH PROJECT, 2022
** BS-my_ftp
** File description:
** main.c
*/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

void server()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int new_sockfd;
    struct sockaddr_in addr;
    struct sockaddr_in cli_addr;
    socklen_t clilen;

    if (sockfd < 0)
        printf("create socket failed\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8082);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        printf("Error binding socket\n");
        return;
    }
    if (listen(sockfd, 5) < 0) {
        printf("Error listening for incoming connections\n");
        return;
    }
    clilen = sizeof(cli_addr);
    if (accept(sockfd, (struct sockaddr *) &cli_addr, &clilen) < 0) {
        printf("Error accepting incoming connection\n");
        return;
    }
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &cli_addr.sin_addr, client_ip, sizeof(client_ip));
    printf("Client connected from %s:%d\n", client_ip, ntohs(cli_addr.sin_port));

    new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    write(new_sockfd, "Hello client!\n", sizeof("Hello client!\n"));
    close(sockfd);
    close(new_sockfd);
}

int main(void) {
    server();

}