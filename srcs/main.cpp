/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:53:40 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/10 16:03:57 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"
#include "../incs/signalManager.hpp"

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

int serverSetup()
{
	int socketServer = socket(AF_INET, SOCK_STREAM, 0);		// Socket d'ecoute
	struct sockaddr_in addrServer;							// in : ipv4  in6 : ipv6
	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(30000);						// host to network
	
	// Demande de l'attachement local de la socket
	if (bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
	{
		std::cerr << "Can't bind" << std::endl;
		return (-1);
	}
	
	// Indique que la socket attend des connexions, fixe la taille de la liste d'attente
	if (listen(socketServer, SOMAXCONN) == -1)								
	{
		std::cerr << "Can't listen" << std::endl;
		return (-1);
	}
	return (socketServer);
}

int acceptConnection(int socketServer)
{
	int socketClient;
	struct sockaddr_in addrClient;
	socklen_t csize = sizeof(addrClient);
	
	// Accepte les demandes de connexion. Crée une nvlle socket connectée et renvoie un fd pour cette socket // Socket de dialogue
	socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
	if (socketClient == -1)
	{
		std::cerr << "Can't accept" << std::endl;
		return (-1);
	}

	// Pas utile, affiche juste des infos sur le client connecté	
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	if (getnameinfo((sockaddr*)&addrClient, csize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
		std::cout << host << " connected on port " << service << std::endl;
	else
		std::cout << "Error" << std::endl;
	
	return (socketClient);
}

void	handleConnection(int socketClient, fd_set *currentSockets, fd_set *writeSockets)
{
	char	buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	
	int bytesReceived = recv(socketClient, buffer, 4096, 0);

	///////////// Send RSP_WELCOME 001 msg
	send(socketClient, ":my_irc 001 amarchal\n", sizeof(":my_irc 001 amarchal\n"), 0);
	
	if (bytesReceived == -1)
	{
		std::cerr << "Error in recv(), Quitting" << std::endl;
		close(socketClient);
		FD_CLR(socketClient, currentSockets);		// remove socket to the set of sockets we are watching
		return ;
	}
	if (bytesReceived == 0)
	{
		std::cout << "Client disconnected" << std::endl;
		close(socketClient);
		FD_CLR(socketClient, currentSockets);		// remove socket to the set of sockets we are watching
		return ;	
	}
	if (buffer[strlen(buffer) - 1] == '\n')
	{
		//////// Echo msg to all clients
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, writeSockets))
				if (i != socketClient)
					send(i, buffer, bytesReceived + 1, 0);
		}
	}
	return ;
}

int main(int ac, char **av)  // ./ircserv [port] [passwd]
{
	int socketServer = serverSetup();
	if (socketServer == -1)
		return (1);
	signalOn(socketServer);	

	fd_set currentSockets;
	fd_set readSockets;
	fd_set writeSockets;

	// initialize current set
	FD_ZERO(&currentSockets);				// initialize
	FD_SET(socketServer, &currentSockets);	// add serverSocket to the set of sockets we are watching
	
	while (1)
	{
		readSockets = currentSockets;		// because select is destructive, it keeps only the sockets ready for reading/writing but we want to keep tracks of all sockets we are watching
		writeSockets = currentSockets;
		
		if (select(FD_SETSIZE, &readSockets, &writeSockets, nullptr, nullptr) == -1)
		{
			std::cerr << "select() error" << std::endl;
			return (1);
		}
		
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &readSockets))
			{
				if (i == socketServer)
				{
					// this is a new connection
					std::cout << "New connection requested" << std::endl;
					int socketClient = acceptConnection(socketServer);
					if (socketClient == -1)
						return (1);
					FD_SET(socketClient, &currentSockets);			// add a new clientSocket to the set of sockets we are watching
					FD_SET(socketClient, &writeSockets);
				}
				else
				{
					std::cout << "something to do with connection " << i << std::endl;
					handleConnection(i, &currentSockets, &writeSockets);							// do what we want to do with this connection
				}
			}
		}
	}
	
	close(socketServer); //// A faire dans un signalHandler
	(void)ac;
	(void)av;
	return (0);
}