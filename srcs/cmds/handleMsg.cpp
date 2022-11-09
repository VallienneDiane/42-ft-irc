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

bool	getClientMsg(int socketClient, std::string content, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string> clientMsg;
	clientMsg = splitMsg(content);
	std::vector<std::string>::iterator it = clientMsg.begin();
	User	&user = userMap.find(socketClient)->second;
	std::string cmds[] = {
		"PASS",
		"NICK",
		"USER",
		"PING",
		"QUIT",
		"JOIN",
		"PART",
		"TOPIC",
		"NAMES",
		"LIST",
		"INVITE",
		"KICK",
		"PRIVMSG",
		"NOTICE",
		"MODE",
	};
	int i = 0;
	int size = sizeof(cmds)/sizeof(std::string);
	for(i = 0; i < size; i++)
	{
		if (cmds[i] == *it)
			break;
	}
	if (i > 14)
		i = -1;
	if (!user.getPass() && i > 0)
	{
		numericReply(ERR_PASSWDMISMATCH, socketClient, userMap, NULL);
		return true;
	}
	if (!fullyRegistered(user) && i > 3)
	{
		std::string	notReg = "You have not registered";
		numericReply(ERR_NOTREGISTERED, socketClient, userMap, &notReg);
		return (0);
	}
	switch (i)
	{
		case 0:
			return (passHandle(user, clientMsg, userMap));
		case 1:
			return (nickHandle(socketClient, *(++it), userMap, channelMap));
		case 2:
			return (userHandle(socketClient, clientMsg, userMap));
		case 3:
			pong(socketClient, clientMsg, content, userMap);
			break;
		case 4:
			return(quit(socketClient, content, userMap, channelMap));
		case 5:
			join(socketClient, clientMsg, userMap, channelMap);
			break;
		case 6:
			part(socketClient, clientMsg, userMap, channelMap);
			break;
		case 7:
			topic(socketClient, clientMsg, userMap, channelMap);
			break;
		case 8:
			names(socketClient, *(++it), userMap, channelMap);
			break;
		case 9:
			list(socketClient, clientMsg, userMap, channelMap);
			break;
		case 10:
			invite(user, clientMsg, userMap, channelMap);
			break;
		case 11:
			kick(socketClient, clientMsg, userMap, channelMap);
			break;
		case 12:
			privmsg(socketClient, clientMsg, content, userMap, channelMap, 1);
			break;
		case 13:
			privmsg(socketClient, clientMsg, content, userMap, channelMap, 2);
			break;
		case 14:
			mode(socketClient, clientMsg, userMap, channelMap);
			break;
		default:
			break;
	}
	return (0);
}

