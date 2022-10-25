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
#include <algorithm>


int sendMsg(const int socket, std::string str)
{
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

int main(int ac, char **av) {
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
	std::string	nick = "NICK fumierBot\r\n";
	std::string user = "USER fumierBot 0 * :\r\n";
	if (ac > 3) {
		std::string pass = "PASS ";
		pass += av[3];
		pass += "\r\n";
		sendMsg(connectSocket, pass);
	}
	sendMsg(connectSocket, nick);
	sendMsg(connectSocket, user);
	std::cout << "data send\n";
	sleep(20);
	return 0;
}