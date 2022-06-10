/*
** EPITECH PROJECT, 2022
** EPITECH-WORKSOP-Chat-Box-in-C
** File description:
** run_server
*/

#include "server.h"

void run_server(server_t *server)
{
	int new_socket, max_sd, sd;
	int addrlen = sizeof(server->addr);

	server->buffer = malloc(sizeof(char) * 10000);
    while(true) {
		if (select(FD_SETSIZE, &server->readfds, &server->writefds,
            &server->fds, NULL) == -1)
			exit (84);
		for (int i = 0; i < FD_SETSIZE; i++) {
			if (FD_ISSET(i, &server->readfds)) {
				if (i == server->socket_client) {
					if ((new_socket = accept(server->socket_client,
						(struct sockaddr *)&server->addr,
						(socklen_t *)&addrlen) == -1))
						exit (83);
					FD_SET(new_socket, &server->fds);
					if (new_socket > server->fdmax)
						server->fdmax = new_socket;
				} else {
					if ((sd = recv(i, server->buffer, strlen(server->buffer), 0)) == -1)
						exit (81);
					if (sd == 0) {
						FD_CLR(i, &server->fds);
						close(i);
					} else {
						for (int j = 0; j < FD_SETSIZE; j++) {
							if (FD_ISSET(j, &server->writefds)) {
								if (send(j, server->buffer, sd, 0) == -1)
									exit (82);
							}
						}
					}
				}
			}
		}
	}
    return;
}
