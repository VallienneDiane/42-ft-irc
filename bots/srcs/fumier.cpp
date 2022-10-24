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

int main(int ac, char **av) {
	if (ac < 3)
	{
		std::cerr << "I need IP + port as arguments\n";
		return 1;
	}
	in_addr_t	ip = inet_addr(av[1]);
	if (ip == INADDR_NONE)
	{
		std::cerr << "your IP argument is invalid\n";
		return 1;
	}
	uint16_t	port = htons(std::atoi(av[2]));
	int socketFumier = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addrFumier;
	unsigned int	sizeAddrFumier = sizeof (addrFumier);
	addrFumier.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrFumier.sin_family = AF_INET;
	addrFumier.sin_port = htons(0);
	if (bind(socketFumier, (const struct sockaddr *) &addrFumier, sizeAddrFumier) == -1)
		std::cerr << "can't bind";
	else
		getsockname(socketFumier, (struct sockaddr *) &addrFumier, &sizeAddrFumier);
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	memset(host, 0, NI_MAXHOST);
	memset(service, 0, NI_MAXSERV);
	if (getnameinfo((sockaddr*)&addrFumier, sizeAddrFumier, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " port Fumier in use : " << service << std::endl;
	}
	else
		std::cout << "Error" << std::endl;

	struct sockaddr_in	addrServ;
	addrServ.sin_addr.s_addr = ip;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = port;
	int servSocket = connect(socketFumier, (const struct sockaddr *) &addrServ, sizeof (addrServ));
	if (servSocket == -1)
	{
		std::cerr << "connection failed\n";
		return 1;
	}
	std::string	connectMsg = "NICK fumier\r\nUSER k k k k\r\n";;
	sleep(1);
	sendMsg(servSocket, connectMsg);
	while (1)
		sleep (20);
	close (servSocket);
	close (socketFumier);
	return 0;
}