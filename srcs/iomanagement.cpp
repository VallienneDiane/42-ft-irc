#include "../incs/ircserv.hpp"

void	delColon(std::string &str)
{
	if (!str.empty() && str.front() == ':')
		str.erase(0,1);
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
    //std::cout << "waiting for client response : \n";
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

int sendMsg(const int socket, std::string &str)
{
    str += "\r\n"; // 
    return (send(socket, str.data(), str.size(), 0));
}

int sendMsg(const int socket, const char * str)
{
    std::cout << "msg send  : " << str;
    return (send(socket, str, strlen(str), 0));
}

std::string delTilde(const std::string &str)
{
	if (str.front() == '~') {
		std::string cpy(str);
		cpy.erase(0, 1);
		return (cpy);
	}
	return str;
}

std::string userSource(const User &user)
{
	std::string source = ":";
	source += user.getNickname();
	source += "!";
	source += delTilde(user.getUsername());
	source += "@";
	source += user.getHostname();
	return (source);
}