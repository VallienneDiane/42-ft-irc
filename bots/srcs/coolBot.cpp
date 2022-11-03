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
	std::cout << "msg send  : " << str;
	return (send(socket, str.data(), str.size(), 0));
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

bool	routineCoolBot(int connectSocket) {

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
	return (routineCoolBot(connectSocket));
}