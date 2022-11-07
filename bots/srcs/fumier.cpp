/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fumier.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:21:23 by njaros            #+#    #+#             */
/*   Updated: 2022/11/07 15:07:01 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <csignal>
#include <set>

bool    isCrlf(std::string str)
{
	std::string::size_type size = str.size();
	return (size >= 2 && str[size - 2] == '\r' && str[size - 1] == '\n');
}

int assignReadValue(int &a, const int b)
{
	a = b;
	return b;
}

int receiveMsg(const int socket, std::string &buffer)
{
	buffer.clear();
	char    lineRead[4096];
	memset(lineRead, 0, 4096);
	int     rd;
	while (assignReadValue(rd, recv(socket, lineRead, 4096, 0)) && rd != -1)
	{
		buffer += lineRead;
		if (lineRead[rd] == '\0' || isCrlf(buffer))
			return (buffer.size());
		memset(lineRead, 0, 4096);
	}
	return rd;
}

std::string takeCommand(std::string &command)
{
	std::string commandDelivered;
	size_t found = command.find("\r\n");
	if (found != std::string::npos)
	{
		commandDelivered.assign(command, 0, found);
		command.erase(0, found + 2);
	}
	return (commandDelivered);
}

int sendMsg(const int socket, std::string str)
{
	str += "\r\n";
	// std::cout << "msg send  : " << str;
	return (send(socket, str.data(), str.size(), 0));
}

std::string	parseChan(std::string &str)
{
	std::string::size_type	found = str.find('#');
	std::string::size_type	spaceFound = str.find(' ', found);
	std::string	parsed = str.substr(found, spaceFound - found);
	return (parsed);
}

int	connection(char **av)
{
	struct addrinfo	hints;
	struct addrinfo *res = NULL;
	int				connectSocket;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(av[1], av[2], &hints, &res))
	{
		std::cerr << "Can't get addr\n";
		return -1;
	}
	connectSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (connectSocket == -1)
	{
		std::cerr << "Can't do socket\n";
		freeaddrinfo(res);
		return -1;
	}
	if (connect(connectSocket, res->ai_addr, (int)res->ai_addrlen) == SO_ERROR) {
		std::cerr << "Can't connect to server\n";
		close(connectSocket);
		freeaddrinfo(res);
		connectSocket = -1;
	}
	return connectSocket;
}

bool	getIn(int servSocket, int ac, char **av)
{
	std::string	nick = "NICK fumierBot";
	std::string user = "USER fumierBot 0 * :";
	if (ac > 3) {
		std::string pass = "PASS ";
		pass += av[3];
		sendMsg(servSocket, pass);
	}
	sendMsg(servSocket, nick);
	sendMsg(servSocket, user);
	std::cout << "connection data send\n";
	receiveMsg(servSocket, nick);
	if (nick.find("001") != std::string::npos) {
		std::cout << "we are welcomed\n";
		return false;
	}
	return true;
}

bool	spamLoop(int servSocket, std::set<std::string> &chanTab)
{
	int	i;
	std::string fumier = " :FUMIEEEEEERRRRRR!!!!!!";
	std::set<std::string>::iterator	end = chanTab.end();
	for (std::set<std::string>::iterator begin = chanTab.begin(); begin != end; ++begin) {
		i = 0;
		std::string	cmd = "PRIVMSG ";
		cmd += *begin;
		cmd += fumier;
		while (i++ < 42) {
			if (sendMsg(servSocket, cmd) == -1)
				return true;
		}
	}
	sleep(5);
	return false;
}

bool	joinChan(int servSocket, std::set<std::string> &tab)
{
	std::set<std::string>::iterator end = tab.end();
	for (std::set<std::string>::iterator begin = tab.begin(); begin != end; ++begin) {
		std::string cmd = "JOIN ";
		cmd += *begin;
		if (sendMsg(servSocket, cmd) == -1)
			return true;
	}
	return false;
}

bool	routineFumier(int servSocket)
{
	while (1) {
		std::string buffer = "LIST";
		std::string	sentence;
		std::set<std::string> chanTab;
		int rd;
		sendMsg(servSocket, buffer);
		rd = receiveMsg(servSocket, buffer);
		if (!rd || rd == -1) {
			std::cout << "end of communication : " << rd << std::endl;
			return 0;
		}
		sentence = takeCommand(buffer);
		while (!sentence.empty()) {
			if (sentence.find('#') != std::string::npos)
			{
				std::string newChan = parseChan(sentence);
				chanTab.insert(newChan);
			}
			sentence = takeCommand(buffer);
		}
		if (chanTab.empty()) {
			sleep(5);
		}
		else {
			if (joinChan(servSocket, chanTab))
				return 1;
			if (spamLoop(servSocket, chanTab))
				return 1;
		}
	}
}

int	main(int ac, char **av) {
	if (ac < 3)
	{
		std::cerr << "I need IP + port as arguments (+ pass if needed)\n";
		return 1;
	}

	int	connectSocket = connection(av);
	if (connectSocket == -1)
	{
		std::cerr << "connection failed\n";
		return 1;
	}
	std::cout << "connected\n";
	if (getIn(connectSocket, ac, av))
		return 1;
	return (routineFumier(connectSocket));
}