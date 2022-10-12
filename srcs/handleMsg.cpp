/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/12 10:21:34 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

std::vector<std::string> splitMsg(std::string content)
{
	char *words = new char [content.length()+1]; //to copy string to chat to use strtok
	std::strcpy(words, content.c_str()); 		//copy all client infos in words (cap, nick, user)
	
	char *line = strtok(words, " ");			 //split words into tokens with " "
	std::vector<std::string> clientInfos;		//create tab with client infos
	
	while(line != NULL)
	{
		clientInfos.push_back(line);
		line = strtok(NULL, "\r \n");
	}
	delete[] words;
	return (clientInfos);
}

bool	getInfosClient(int socketClient, std::string content, std::map<int, User> &userMap)
{
	std::vector<std::string> clientInfos;
	size_t i = 0;
	clientInfos = splitMsg(content);
	std::cout << content << std::endl;
	std::vector<std::string>::iterator itEnd = clientInfos.end();
	std::string cmds[] = {
		"CAP",
		"AUTHENTICATE",
		"PASS",
		"NICK",
		"USER",
		"PING",
		"PONG",
		"OPER",
		"QUIT",
		"ERROR"
	};
	for(std::vector<std::string>::iterator it = clientInfos.begin(); it != itEnd; it++)
	{
		for(i = 0; i < it->size(); i++)
		{
			if (cmds[i] == *it)
				break;
		}
		switch (i)
		{
			case 0:
				std::cout << "cap " << std::endl;
				break;
			case 1:
				std::cout << "authenticate " << std::endl;
				break;
			case 2:
				std::cout << "pass " << std::endl;
				break;
			case 3:
				std::cout << "nick " << std::endl;
				return (nickHandle(socketClient, *(++it), userMap));
				break;
			case 4:
				std::cout << "user " << std::endl;
				userHandle(socketClient, *(++it), userMap);
				break;
			case 5:
				std::cout << "ping " << std::endl;
				break;
			case 6:
				std::cout << "pong " << std::endl;
				break;
			case 7:
				std::cout << "oper " << std::endl;
				break;
			case 8:
				std::cout << "quit " << std::endl;
				break;
			case 9:
				std::cout << "error " << std::endl;
				break;
			default:
				break;
		}
		// if (it->compare("NICK") == 0)
		// {
		// 	std::cout << "nick " << std::endl;
		// }
		// if (it->compare("USER") == 0)
		// {
		// 	std::string username = *(++it);
		// 	std::cout << "user " << std::endl;
		// }
	}
	return (0);
}

