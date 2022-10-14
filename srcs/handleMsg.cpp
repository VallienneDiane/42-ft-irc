/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/14 13:56:37 by dvallien         ###   ########.fr       */
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

bool	getInfosClient(int socketClient, std::string content, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string> clientInfos;
	clientInfos = splitMsg(content);
	std::cout << content << std::endl;
	std::vector<std::string>::iterator it = clientInfos.begin();
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
		"ERROR",
		"JOIN",
		"PART",
		"TOPIC",
		"NAMES",
		"LIST",
		"INVITE",
		"KICK",
		"PRIVMSG",
		"NOTICE"
	};
	std::cout << BGREEN << "CMD name : " << *(clientInfos.begin()) << END << std::endl;
	
	int i = 0;
	int size = sizeof(cmds)/sizeof(std::string);
	for(i = 0; i < size; i++)
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
			return (userHandle(socketClient, *(++it), *(it + 3), userMap));
		case 5:
			std::cout << "ping " << std::endl;
			// return (ping(socketClient));
			break;
		case 6:
			std::cout << "pong " << std::endl;
			return (pong(socketClient));
		case 7:
			std::cout << "oper " << std::endl;
			break;
		case 8:
			std::cout << "quit " << std::endl;
			break;
		case 9:
			std::cout << "error " << std::endl;
			break;
		case 10:
			std::cout << "join " << std::endl;
			return (join(socketClient, *(++it), userMap, channelMap));
			break;
		case 11:
			std::cout << "part " << std::endl;
			return(part(socketClient, *(it + 2), userMap, channelMap));
			break;
		case 12:
			std::cout << "topic " << std::endl;
			break;
		case 13:
			std::cout << "names " << std::endl;
			return (names(socketClient, *(++it), userMap, channelMap));
			break;
		case 14:
			std::cout << "list " << std::endl;
			break;
		case 15:
			std::cout << "invite " << std::endl;
			break;
		case 16:
			std::cout << "kick " << std::endl;
			break;
		case 17:
			std::cout << "privmsg " << std::endl;
			break;
		case 18:
			std::cout << "notice " << std::endl;
			break;
		default:
			break;
	}
	return (0);
}

