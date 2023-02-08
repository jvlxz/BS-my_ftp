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
#include <sys/select.h>

void server() {
    int sockfd;
    struct sockaddr_in addr;
    int one = 1;
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int ndfs;
    fd_set cur_socket, next_socket;

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
    FD_ZERO(&cur_socket);
    FD_SET(sockfd, &cur_socket);
    while(1) {
        next_socket = cur_socket;
        if (select(FD_SETSIZE, &next_socket, NULL, NULL, NULL) < 0) {
            printf("Error selecting socket");
        }
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &next_socket)) {
                if (i == sockfd){
                    int new_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                    if (new_sockfd < 0) {
                        printf("Error accepting connection\n");
                    } else {
                        FD_SET(new_sockfd, &cur_socket);
                        printf("Connection accepted\n");
                        int n = write(new_sockfd, "Hello client!\n", sizeof("Hello client!\n"));
                        if (n < 0) {
                            printf("Error writing to socket\n");
                        }
                        close(new_sockfd);
                        printf("client closed\n");
                        FD_CLR(new_sockfd, &cur_socket);
                    }
                }
            }
        }
    }
    close(sockfd);
}

int main(void) {
    server();
    return 0;
}
