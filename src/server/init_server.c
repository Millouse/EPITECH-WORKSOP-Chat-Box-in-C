/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** init_server
*/

#include "server.h"

server_t *init_server(char *ip_addr, int port)
{
    server_t *server = malloc(sizeof(server_t));
    int sockfd = socket(AF_INET , SOCK_STREAM , 0);
    int addrlen = sizeof(server->addr);
    int opt = 1;

    if (sockfd == -1)
        exit (84);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        exit (84);
    server->ip_addr = ip_addr;
    server->port = port;
    server->addr.sin_addr.s_addr = inet_addr(ip_addr);
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(port);
    if (bind(sockfd,(struct sockaddr *)&server->addr, sizeof(server->addr)) == -1)
        exit (84);
    if (listen(sockfd, 3) == -1)
        exit (84);
    if ((server->socket_client = accept(sockfd, (struct sockaddr *)&server->addr, (socklen_t *)&addrlen)) == -1)
        exit (84);
    return server;
}