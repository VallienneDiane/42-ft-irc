/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:53:40 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/21 11:09:49 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"
#include "../incs/signalManager.hpp"
#include "../incs/User.hpp"
/* 
	The client-server infrastructure mean a server socket listens for one or more connections from a client socket.
	Two sockets (socket client and socket server) must be of the same type and in the same domain (Unix domain or Internet domain) to enable communication btw hosts.
*/

std::pair<int, std::string>	parseEntries(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << "You must type ./irc <port> <password>\n";
		exit (1);
	}
	return (std::make_pair(atoi(av[1]), av[2]));
}

int serverSetup(int port)
{
	// CREATE SOCKET AND DEFINE SERVER ADDR
	int socketServer = socket(AF_INET, SOCK_STREAM, 0);		// create the socket (AF_INET : socket family, Sock_STREAM : type of socket)
	struct sockaddr_in addrServer;							// in : ipv4  in6 : ipv6, contains technique informations of socket
	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");	// define server address
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);						// host to network
	unsigned int	sizeAddr = sizeof (addrServer);
	// BIND ADDR IP & PORT TO THE SOCKET
	// Bind will attach the socket directly to the port and address we defined in the SOCKADDR_IN struct.
	if (bind(socketServer, (const struct sockaddr *)&addrServer, sizeAddr) == -1)
	{
		std::cerr << "Can't bind" << std::endl;
		close(socketServer);
		return (-1);
	}
	else
		getsockname(socketServer, (struct sockaddr *) &addrServer, &sizeAddr);
	// LISTEN THE PORT ON THE SOCKET, WAITING CONNEXIONS
	// Listen will listen to the port on the socket. The 2nd parameter is the max number of connections that will be listened to at the same time.
	if (listen(socketServer, SOMAXCONN) == -1)								
	{
		std::cerr << "Can't listen" << std::endl;
		return (-1);
	}
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	if (getnameinfo((sockaddr*)&addrServer, sizeAddr, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		if (!std::strcmp(service, "ircd"))
			std::cout << host << " SERVER PORT : " << "6667 (ou ircd pour les intimes)\n";
		else
			std::cout << host << " SERVER PORT : " << service << std::endl;
	}
	else {
		std::cerr << "can't get server information ?? \n";
		return (-1);
	}
	return (socketServer);
}

int acceptConnection(int socketServer, std::map<int, User> &userMap)
{
	int socketClient;
	struct sockaddr_in addrClient;
	socklen_t csize = sizeof(addrClient);
	// ACCEPT CONNECTION DEMAND 
	// Accept a connection on a socket and send back fd for this socket = dialog socket
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
		std::cerr << "Error" << std::endl;
    userMap[socketClient];
	userMap[socketClient].setSocket(socketClient);
	return (socketClient);
}

void	handleConnection(int socketClient, fd_set *currentSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::string buffer;
    std::string sentence;
	int bytesReceived = receiveMsg(socketClient, buffer); //RECEIVE A CLIENT MSG ON A SOCKET
	// std::cout << CYAN << "Enter command : " << buffer << END << std::endl;

	if (bytesReceived == -1)
	{
		std::string reason = "QUIT :Client crashed !!";
		quit(socketClient, reason, userMap, channelMap);
		FD_CLR(socketClient, currentSockets); // remove socket to the set of sockets we are watching
		return ;
	}
	if (bytesReceived == 0)
	{
		std::string reason = "QUIT :Client closed";
		quit(socketClient, reason, userMap, channelMap);
		FD_CLR(socketClient, currentSockets); // remove socket to the set of sockets we are watching
		return ;	
	}
	else //RECEIVE CLIENT CMDS AND EXECUTE IN FUNCTION getClientMsg()
	{
        User &current = userMap.find(socketClient)->second;
        current.appendCommand(buffer);
		sentence = current.deliverCommand();
		while (!sentence.empty())
        {
            if (getClientMsg(socketClient, sentence, userMap, channelMap))
            {
                FD_CLR(socketClient, currentSockets);
                return ;
            }
            sentence = current.deliverCommand();
        }
	}
	return ;
}

int main(int ac, char **av)
{
	std::pair<int, std::string>	entries = parseEntries(ac, av);
	struct timeval tv;
	std::map<int, User> userMap;
	std::map<std::string, Channel> channelMap;
	
	tv.tv_sec = 0;
	tv.tv_usec = 5;
	int socketServer = serverSetup(entries.first); //create socket, bind port & socket, listen port
	if (socketServer == -1)
		return (1);
	setPass(entries.second); //set server passwd
	signalOn(socketServer);	

	// fd struct : stock all fd ready to read/write
	fd_set currentSockets;
	fd_set readSockets;
	fd_set writeSockets;
	// INITIALIZE CURRENT SET
	FD_ZERO(&currentSockets);
	FD_SET(socketServer, &currentSockets);	// add serverSocket to the set of sockets we are watching
	while (1)
	{
		readSockets = currentSockets; // because select is destructive, it keeps only the sockets ready for reading/writing but we want to keep tracks of all sockets we are watching
		writeSockets = currentSockets;
		//SELECT : NON-BLOCKING FUNCTION - EQUIVALENT TO POLL()
		//allow a program to monitor multiple fd, waiting for at least one of the fd to become "ready" for some actions like read or write
		if (select(FD_SETSIZE, &readSockets, &writeSockets, NULL, &tv) == -1)
		{
			std::cerr << "select() error" << std::endl;
			return (1);
		}
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &readSockets)) // if socket is ready to read
			{
				if (i == socketServer) // if socket server same that socket client : REQUEST NEW CONNECTION/USER
				{
					int socketClient = acceptConnection(socketServer, userMap);
					if (socketClient == -1)
						return (1);
					FD_SET(socketClient, &currentSockets); // add a new clientSocket to the set of sockets we are watching
				}
				else //Already know user/socket : GET CLIENT CMDS
					handleConnection(i, &currentSockets, userMap, channelMap); // RECEIVE CLIENT CMDS
			}
			if (FD_ISSET(i, &writeSockets) && userMap[i].getBufferMsg().size() != 0)
				userMap[i].deliverBufferMsg();
		}
	}
	close(socketServer);
	return (0);
}