/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include "server.h"

void run_server(server_t *server)
{
    char server_reply[6000];
	char *msg = "coucou !!!";

	if (send(server->socket_client , msg , strlen(msg) , 0) < 0) {
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	if (recv(server->socket_client, server_reply , 6000 , 0) < 0) {
		perror("recv");
	}
    printf("Reply received\n");
	printf("%s\n" ,server_reply);
    return;
}
