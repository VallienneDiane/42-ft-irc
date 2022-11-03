/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/21 17:33:07 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

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

bool	getClientMsg(int socketClient, std::string content, fd_set *writeSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string> clientMsg;
	clientMsg = splitMsg(content);
	std::cout << content << std::endl;
	std::vector<std::string>::iterator it = clientMsg.begin();
	User	&user = userMap.find(socketClient)->second;
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
		"NOTICE",
	};
	// std::cout << BGREEN << "CMD name : " << *(clientMsg.begin()) << END << std::endl;
	int i = 0;
	int size = sizeof(cmds)/sizeof(std::string);
	for(i = 0; i < size; i++)
	{
		if (cmds[i] == *it)
			break;
	}
	if (!user.getPass() && i > 2)
	{
		numericReply(ERR_PASSWDMISMATCH, socketClient, userMap, NULL);
		return true;
	}
	if (!fullyRegistered(user) && i > 5)
	{
		std::string	notReg = "You have not registered";
		numericReply(ERR_NOTREGISTERED, socketClient, userMap, &notReg);
		return (0);
	}
	switch (i)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			return (passHandle(user, clientMsg, userMap));
			break;
		case 3:
			return (nickHandle(socketClient, *(++it), userMap, channelMap));
			break;
		case 4:
			return (userHandle(socketClient, clientMsg, userMap));
		case 5:
			return (pong(socketClient, content));
		case 6:
			// std::cout << "pong " << std::endl;
			//return (pong(socketClient, content));
			break;
		case 7:
			// std::cout << "oper " << std::endl;
			break;
		case 8:
			return (quit(socketClient, content, userMap, channelMap));
			break;
		case 9:
			// std::cout << "error " << std::endl;
			break;
		case 10:
			return (join(socketClient, *(++it), userMap, channelMap));
			break;
		case 11:
			return(part(socketClient, *(++it), clientMsg, userMap, channelMap));
			break;
		case 12:
			return(topic(socketClient, *(++it), clientMsg, userMap, channelMap));
			break;
		case 13:
			return (names(socketClient, *(++it), userMap, channelMap));
			break;
		case 14:
			list(socketClient, clientMsg, userMap, channelMap);
			break;
		case 15:
			invite(user, clientMsg, userMap, channelMap);
			break;
		case 16:
			kick(socketClient, clientMsg, userMap, channelMap);
			break;
		case 17:
			privmsg(socketClient, clientMsg, writeSockets, userMap, channelMap, 1);
			break;
		case 18:
			privmsg(socketClient, clientMsg, writeSockets, userMap, channelMap, 2);
			break;
		case 19:
			mode(socketClient, clientMsg, userMap, channelMap);
			break;
		default:
			break;
	}
	return (0);
}

