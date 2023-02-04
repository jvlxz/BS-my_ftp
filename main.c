/*
** EPITECH PROJECT, 2022
** BS-my_ftp
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void server() {
    int sockfd, new_sockfd;
    struct sockaddr_in addr;
    int one = 1;
    struct sockaddr_in cli_addr;
    socklen_t clilen;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        return;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t lenSocket = sizeof(struct sockaddr);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, lenSocket) < 0) {
        printf("Error setting socket options\n");
        return;
    }

    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        printf("Error binding socket\n");
        return;
    }

    if (listen(sockfd, 5) < 0) {
        printf("Error listening for incoming connections\n");
        return;
    }

    clilen = sizeof(cli_addr);
    if ((new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
        printf("Error accepting incoming connection\n");
        return;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &cli_addr.sin_addr, client_ip, sizeof(client_ip));
    printf("Client connected from %s:%d\n", client_ip, ntohs(cli_addr.sin_port));

    write(new_sockfd, "Hello client!\n", sizeof("Hello client!\n"));
    close(new_sockfd);
}

int main(void) {
    server();
    return 0;
}
