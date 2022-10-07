/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:53:40 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/07 14:09:23 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Ircserv.hpp"

/* The client-server infrastructure mean a server socket listens for one or more connections from a client socket.
	Two sockets must be of the same type and in the same domain (Unix domain or Internet domain) to enable communication btw hosts.

// CREATE A SOCKET //
	//socket(family socket, type socket, 0);
	//SOCK stream : direct connection btw 2 computers et send packages
	//SOCK dgram : send directly package to destination without accept or connect
// BIND ADDR IP & PORT TO A SOCKET
	//struct of SOCKADDR contains technique informations of socket
	//family socket, the type AF_INET
	//port to connect
	//define server address
	//bind : attach socket to port and address (socket, struct SOCKADDR_IN, size struct)
*/

int main(int ac, char **av) // ./ircserv [port] [passwd]
{
	(void)ac;
	(void)av;
	// ********* CREATE A SOCKET ********* //
	int listening = socket(AF_INET, SOCK_STREAM, 0); 
	if (listening == -1)
	{
		std::cerr << "Can't create a socket" << std::endl;
		return (1);
	}
	// ********* BIND ADDR IP & PORT TO A SOCKET ********* //
	struct sockaddr_in hint; 
	hint.sin_family = AF_INET; 
	// int port = atoi(av[1]);
	hint.sin_port = htons(6000); 
	hint.sin_addr.s_addr = INADDR_ANY; // "127.0.0.1"
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	// ********* LISTEN THE PORT ********* //
	listen(listening, SOMAXCONN);
	std::cout << "Please enter message :" <<  std::endl;
	// ********* WAIT FOR CONNECTION ********* //
	while(1)
	{
		sockaddr_in	clientaddr;
		socklen_t clientSize = sizeof(clientaddr);
		int clientSocket = accept(listening,(sockaddr*)&clientaddr, &clientSize);
		if (clientSocket != 0)
		{
			int n;
			char buffer[256];
			
			bzero(buffer,256);
    		fgets(buffer,255,stdin);
    		n = write(clientSocket, buffer, strlen(buffer));
    		bzero(buffer,256);
    		n = read(clientSocket, buffer, 255);
    		printf("%s\n", buffer);
			// send(clientSocket, "Hello", 5, 0); FORMAT A TROUVER
			close(clientSocket);
		}
	}
	return (0);
}