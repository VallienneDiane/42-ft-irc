/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iomanagement.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:24:10 by njaros            #+#    #+#             */
/*   Updated: 2022/11/07 13:24:10 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

void	fillString(std::string &str, size_t s)
{
	if ((s / 10) > 0)
	{
		fillString(str, s / 10);
		fillString(str, s % 10);
	}
	if ((s / 10) == 0)
		str += s + '0';
}

std::string	size_tToString(size_t s)
{
	std::string	str;

	fillString(str, s);
	return (str);
}

void	delColon(std::string &str)
{
	if (!str.empty() && str[0] == ':')
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
    buffer.clear();
    char    lineRead[4096];
    memset(lineRead, 0, 4096);
    int     rd;
    while (assignReadValue(rd, recv(socket, lineRead, 4096, 0)) && rd != -1) // recv() = read()
    {
        buffer += lineRead;
        if (lineRead[rd] == '\0' || isCrlf(buffer))
            return (buffer.size());
        memset(lineRead, 0, 4096);
    }
    return rd;
}

int sendMsg(const int socket, std::string str)
{
    str += "\r\n";
    std::cout << "msg send  : " << str;
    return (send(socket, str.data(), str.size(), 0));
}

std::string delTilde(const std::string &str)
{
	if (str[0] == '~') {
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