/*
** EPITECH PROJECT, 2022
** BS-my_ftp
** File description:
** client.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void client(char *adress, int port)
{
    int sockclient;
    struct sockaddr_in addr;
    int one = 1;
    if ((sockclient = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        return;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(adress);
    socklen_t lenSocket = sizeof(struct sockaddr);
    if(connect(sockclient, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return;
    }
    char buffer[256];
    int n = read(sockclient, buffer, sizeof(buffer));
    if (n < 0) {
        printf("Error reading from socket\n");
        return;
    }
    printf("%s", buffer);
}

int main(int ac, char **av) {
    (void)ac;
    client(av[1], atoi(av[2]));
    return 0;
}