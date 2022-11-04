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

int	compareTime(timeval &t1, timeval &t2)
{
	int	tempsSec;

	gettimeofday(&t2, 0);
	//std::cout << "compare = " << t1.tv_sec << " et current = " << t2.tv_sec << std::endl;
	tempsSec = (t2.tv_sec - t1.tv_sec);
	if (tempsSec >= 5) {
		gettimeofday(&t1, 0);
		std::cout << "after reset of compare, compare = " << t1.tv_sec << std::endl;
		return (1);
	}
	return (0);
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

/*bool	askListAndJoin(int connectSocket, std::set<std::string> &chan) {
	
}*/

bool	routineCoolBot(int connectSocket, char *str, char *answer) {
	(void) str;
	(void) answer;
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
		if (FD_ISSET(0, &readSockets)) {
			std::string msg;
			int err = receiveMsg(connectSocket, msg);
			if (err == -1 && errno != EAGAIN)
				return (errno);
			else if (err == 0)
				return (0);
			/*else if (parseCmd(connectSocket, msg, str,
							  answer)) // ICI Localiser les privmsg et repondre si c'est le code voulu
				return (errno);*/
			}
		if (compareTime(compare, current)) {
			//if (askListAndJoin(connectSocket, chan))
			//	return (errno);
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