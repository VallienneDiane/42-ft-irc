/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:41:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/21 11:39:50 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

void	msgToChannel(int socketClient, Channel &channel, std::string msg, std::map<int, User> &userMap, int type)
{
	///////// FOR EACH USER IN THE CHANNEL
	for (std::set<int>::iterator channelUser = channel.getUserSet().begin(); channelUser != channel.getUserSet().end(); channelUser++)
	{
		////////// CHECK IF USER SOCKET IS READY FOR WRITING
		if (*channelUser != socketClient && !((*channelUser == socketClient) && (type == 1)))
			userMap[*channelUser].addMsgToBuffer(msg);
	}
}

void	msgToUser(int socketClient, User &user, std::string msg, std::map<int, User> &userMap, bool firstMsg, int type)
{
	////////// CHECK IF USER SOCKET IS READY FOR WRITING
	if (user.getSocket() != socketClient)
		user.addMsgToBuffer(msg);
	if (firstMsg && type == 1)
		userMap[socketClient].addMsgToBuffer(msg);
}

void	linkUsers(int socketClient, int socketUser, std::map<int, User> &userMap)
{
	userMap[socketClient].addPrivMsg(socketUser);
	userMap[socketUser].addPrivMsg(socketClient);
}

std::string privMsgParseData(std::string &data, std::map<int, User> &userMap, int socketClient, int type)
{
	std::string	msg = userSource(userMap[socketClient]);
	std::string::size_type	space;

	if (type == 1)
		msg += " PRIVMSG ";
	else
		msg += " NOTICE ";
	for (char i = 0; i < 2; i++) {
		space = data.find(' ');
		space = data.find_first_not_of(' ', space);
	}
	msg.append(data, space, std::string::npos);
	return (msg);
}

bool	privmsg(int socketClient, std::vector<std::string> &split, std::string &rawData, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap, int type)
{
	std::map<std::string, Channel>::iterator channelEnd = channelMap.end();

	if (split.size() < 3)
	{
		if (type == 1)
			numericReply(ERR_NEEDMOREPARAMS, socketClient, userMap, &split[0]);
		return false;
	}
	std::string	dest = split[1];
	/////////// SEND MSG TO CHANNEL
	if (dest[0] == '#')
	{
		std::map<std::string, Channel>::iterator chanIt = channelMap.find(dest);
		/////////// CHECK IF CHANNEL EXIST
		if (chanIt != channelEnd)
		{
			/////////// CHECK IF USER IS IN CHANNEL
			if (chanIt->second.isInUserSet(socketClient).first) 
			{
				std::string	msg = privMsgParseData(rawData, userMap, socketClient, type);
				msgToChannel(socketClient, chanIt->second, msg, userMap, type);
			}
			else
				numericReply(ERR_CANNOTSENDTOCHAN, socketClient, userMap, &dest);
		}
		else if (type == 1)
			numericReply(ERR_NOSUCHCHANNEL, socketClient, userMap, &dest);
	}
	/////////// SEND MSG TO USER
	else
	{
		/////////// CHECK IF USER EXIST
		for (std::map<int, User>::iterator user = userMap.begin(); user != userMap.end(); user++)
		{
			if (user->second.getNickname() == dest)
			{
				std::string	msg = privMsgParseData(rawData, userMap, socketClient, type);
				//////////// ADD USER IN CONTACT LIST IF NOT ALLREADY IN IT
				if (userMap[socketClient].isInPrivMsg(user->second.getSocket()) == false)
				{
					linkUsers(socketClient, user->second.getSocket(), userMap);
					msgToUser(socketClient, user->second, msg, userMap, true, type);
				}
				else
					msgToUser(socketClient, user->second, msg, userMap, false, type);
				return (0);
			}
		}
		/////////// IF USER DOES NOT EXIST
		if (type == 1)
			numericReply(ERR_NOSUCHNICK, socketClient, userMap, &dest);
	}
	return (0);
}
