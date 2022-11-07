/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coolBot.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:21:15 by njaros            #+#    #+#             */
/*   Updated: 2022/11/07 15:07:07 by dvallien         ###   ########.fr       */
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
#include <cerrno>
#include <time.h>
#include <sys/time.h>
#include <vector>

int	compareTime(timeval &t1, timeval &t2)
{
	int	tempsSec;

	gettimeofday(&t2, 0);
	tempsSec = (t2.tv_sec - t1.tv_sec);
	if (tempsSec >= 5) {
		gettimeofday(&t1, 0);
		return (1);
	}
	return (0);
}

std::vector<std::string> splitMsg(std::string content)
{
	char *words = new char [content.length()+1]; //to copy string to chat to use strtok
	std::strcpy(words, content.c_str()); 		//copy all client infos in words (cap, nick, user)
	char *line = strtok(words, " ");			//split words into tokens with " "
	std::vector<std::string> clientMsg;			//create tab with client infos
	
	while(line != NULL)
	{
		clientMsg.push_back(line);
		line = strtok(NULL, "\r \n");
	}
	delete[] words;
	return (clientMsg);
}

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

int sendMsg(const int socket, const char * str)
{
	// std::cout << "msg send  : " << str;
	return (send(socket, str, strlen(str), 0));
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
	std::string	nick = "NICK coolBot";
	std::string user = "USER coolBot 0 * :Gerard CoolBotMan";
	if (ac > 5) {
		std::string pass = "PASS ";
		pass += av[5];
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

bool	parseList(int socket, std::vector<std::string> &lst, std::set<std::string> &chan) {
	std::set<std::string>::iterator end = chan.end();
	if (chan.find(lst[3]) == end) {
		std::string msg = "JOIN ";
		msg += lst[3];
		return (sendMsg(socket, msg) == -1);
	}
	return false;
}

void	parseInvite(std::vector<std::string> &lst, std::set<std::string> &chan) {
	chan.insert(lst[3]);
}

bool	parseNames(int socket, std::vector<std::string> &lst, std::set<std::string> &chan) {
	if (chan.insert(lst[3]).second) {
		return false;
	}
	else if (lst.size() == 6) {
		std::string	msg = "PART ";
		msg += lst[3];
		chan.erase(lst[3]);
		return (sendMsg(socket, msg) == -1);
	}
	return false;
}

bool	askNames(int socket, std::set<std::string> &chan) {
	std::set<std::string>::iterator	end = chan.end();
	for (std::set<std::string>::iterator it = chan.begin(); it != end; ++it) {
		std::string msg = "NAMES ";
		msg += *it;
		if (sendMsg(socket, msg) == -1)
			return true;
	}
	return false;
}

bool	parsePrivmsg(int connectSocket, std::vector<std::string> words, std::string buffer, char *strToReplace, char *botAnswer)
{
	if (buffer.find(strToReplace) != std::string::npos)
	{
		std::string msg = "PRIVMSG ";
		msg += words[2];
		msg += " ";
		msg += botAnswer;
		if (sendMsg(connectSocket, msg) == -1)
			return (1);
	}
	return (0);
}

bool	parseCmd(int connectSocket, std::string clientMsg, char *strToReplace, char *botAnswer, std::set<std::string> &chan)
{
	std::string buffer;

	buffer = takeCommand(clientMsg);
	while (!buffer.empty())
	{
		std::vector<std::string> words = splitMsg(buffer);

		if (words[1] == "PRIVMSG") {
			if (parsePrivmsg(connectSocket, words, buffer, strToReplace, botAnswer))
				return (1);
		}
		else if (words[1] == "322") {
			if (parseList(connectSocket, words, chan))
				return (1);
		}
		else if (words[1] == "353") {
			if (parseNames(connectSocket, words, chan))
				return (1);
		}
		else if (words[1] == "INVITE")
			parseInvite(words, chan);
		buffer = takeCommand(clientMsg);
	}
	return (0);
}

bool	routineCoolBot(int connectSocket, char *str, char *answer) {
	std::set<std::string>	chan;
	struct timeval	compare;
	struct timeval	current;
	struct timeval	selectTimeOut;
	fd_set	currentSockets;
	fd_set	readSockets;
	fd_set	writeSockets;
	selectTimeOut.tv_sec = 0;
	selectTimeOut.tv_usec = 50000;
	FD_ZERO(&currentSockets);
	FD_SET(connectSocket, &currentSockets);
	gettimeofday(&compare, 0);
	while (true) {
		readSockets = currentSockets;
		writeSockets = currentSockets;
		if (select(FD_SETSIZE, &readSockets, &writeSockets, NULL, &selectTimeOut) == -1) {
			std::cerr << "select() error\n";
			return (errno);
		}
		if (FD_ISSET(connectSocket, &readSockets)) {
			std::string msg;
			int err = receiveMsg(connectSocket, msg);
			if (err == -1 && errno != EAGAIN)
				return (errno);
			else if (err == 0)
				return (0);
			else if (parseCmd(connectSocket, msg, str, answer, chan))
				return (errno);
			}
		if (compareTime(compare, current)) {
			if ((sendMsg(connectSocket, "LIST\r\n") == -1) ||
			askNames(connectSocket, chan))
				return (errno);
		}
	}
}

int	main(int ac, char **av) {
	if (ac < 5)
	{
		std::cerr << "I need IP + port + \"sentence to awake me\" + \"sentence I answer\" as arguments (+ pass if needed)\n";
		return 1;
	}

	int connectSocket = connection(av);
	if (connectSocket == -1)
	{
		std::cerr << "connection failed\n";
		return 1;
	}
	std::cout << "connected\n";
	if (getIn(connectSocket, ac, av))
		return 1;
	return (routineCoolBot(connectSocket, av[3], av[4]));
}