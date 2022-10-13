/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:53:40 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 12:59:20 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"
#include "../incs/signalManager.hpp"
#include "../incs/User.hpp"
/* 
	The client-server infrastructure mean a server socket listens for one or more connections from a client socket.
	Two sockets must be of the same type and in the same domain (Unix domain or Internet domain) to enable communication btw hosts.
*/
int serverSetup()
{
	int socketServer = socket(AF_INET, SOCK_STREAM, 0);		// listening Socket
	struct sockaddr_in addrServer;							// in : ipv4  in6 : ipv6, contains technique informations of socket
	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6667);						// host to network
	
	// BIND ADDR IP & PORT TO A SOCKET
	if (bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
	{
		std::cerr << "Can't bind" << std::endl;
		close(socketServer);
		return (-1);
	}
	// SOCKET WAITING CONNEXIONS, FIX THE WAITING LIST
	if (listen(socketServer, SOMAXCONN) == -1)								
	{
		std::cerr << "Can't listen" << std::endl;
		return (-1);
	}
	return (socketServer);
}

int acceptConnection(int socketServer, std::map<int, User> &userMap)
{
	int socketClient;
	struct sockaddr_in addrClient;
	socklen_t csize = sizeof(addrClient);
	// User	newUser;
	// ACCEPT CONNEXION DEMAND. CREATE NEW SOCKET AND SEND BACK FD FOR THIS SOCKET : DIALOG SOCKET
	socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
	if (socketClient == -1)
	{
		std::cerr << "Can't accept" << std::endl;
		return (-1);
	}
	// DISPLAY INFOS ON CONNECTED CLIENT	
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	if (getnameinfo((sockaddr*)&addrClient, csize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
		userMap[socketClient].setHostname(host);
	}
	else
		std::cout << "Error" << std::endl;
    userMap[socketClient];
	userMap[socketClient].setSocket(socketClient);
	return (socketClient);
	(void)userMap;	
}

void	handleConnection(int socketClient, fd_set *currentSockets, fd_set *writeSockets, std::map<int, User> &userMap)
{
	std::string buffer;
    std::string sentence;
	int bytesReceived = receiveMsg(socketClient, buffer);

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
		userMap.erase(socketClient);
		close(socketClient);
		FD_CLR(socketClient, currentSockets);		// remove socket to the set of sockets we are watching
		return ;	
	}
	else
	{
        User &current = userMap.find(socketClient)->second;
        current.appendCommand(buffer);
		sentence = current.deliverCommand();
		while (!sentence.empty())
        {
            if (getInfosClient(socketClient, sentence,userMap))
            {
                FD_CLR(socketClient, currentSockets);
                return ;
            }
            sentence = current.deliverCommand();
        }
		//////// Echo msg to all clients
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, writeSockets))
				if (i != socketClient)
					sendMsg(i, buffer);
		}
	}
	return ;
}

int main(int ac, char **av)  // ./ircserv [port] [passwd]
{
	(void)ac;
	(void)av;

	std::map<int, User> userMap; 
	int socketServer = serverSetup();
	if (socketServer == -1)
		return (1);
	signalOn(socketServer);	

	fd_set currentSockets;
	fd_set readSockets;
	fd_set writeSockets;

	// INITIALIZE CURRENT SET
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
					int socketClient = acceptConnection(socketServer, userMap);
					if (socketClient == -1)
						return (1);
					FD_SET(socketClient, &currentSockets);			// add a new clientSocket to the set of sockets we are watching
					FD_SET(socketClient, &writeSockets);
				}
				else
				{
					std::cout << "something to do with connection " << i << std::endl;
					handleConnection(i, &currentSockets, &writeSockets, userMap);		// do what we want to do with this connection
				}
			}
		}
	}
	close(socketServer); // TO DO IN signalHandler
	return (0);
}