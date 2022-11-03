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

void	msgToChannel(int socketClient, Channel &channel, fd_set *writeSockets, std::string msg)
{
	///////// FOR EACH USER IN THE CHANNEL
	for (std::set<int>::iterator channelUser = channel.getUserSet().begin(); channelUser != channel.getUserSet().end(); channelUser++)
	{
		////////// CHECK IF USER SOCKET IS READY FOR WRITING
		if (FD_ISSET(*channelUser, writeSockets) && *channelUser != socketClient)
			sendMsg(*channelUser, msg);
	}
}

void	msgToUser(int socketClient, User &user, fd_set *writeSockets, std::string msg, bool firstMsg)
{
	////////// CHECK IF USER SOCKET IS READY FOR WRITING
	if (FD_ISSET(user.getSocket(), writeSockets) && user.getSocket() != socketClient)
		sendMsg(user.getSocket(), msg);
	if (firstMsg)
		sendMsg(socketClient, msg);
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

bool	privmsg(int socketClient, std::vector<std::string> &split, std::string &rawData, fd_set *writeSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap, int type)
{
	if (split.size() < 3)
	{
		numericReply(ERR_NEEDMOREPARAMS, socketClient, userMap, &rawData);
		return false;
	}
	std::string	dest = split[1];
	/////////// SEND MSG TO CHANNEL
	if (dest[0] == '#')
	{
		std::map<std::string, Channel>::iterator chanIt = channelMap.find(dest);
		/////////// CHECK IF CHANNEL EXIST
		if (chanIt != channelMap.end())
		{
			/////////// CHECK IF USER IS IN CHANNEL
			if (chanIt->second.isInUserSet(socketClient).first) {
				std::string	msg = privMsgParseData(rawData, userMap, socketClient, type);
				msgToChannel(socketClient, chanIt->second, writeSockets, msg);
			}
		}
		else
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
					msgToUser(socketClient, user->second, writeSockets, msg, true);
				}
				else
					msgToUser(socketClient, user->second, writeSockets, msg, false);
				return (0);
			}
		}
		/////////// IF USER DOES NOT EXIST
		numericReply(ERR_NOSUCHNICK, socketClient, userMap, &dest);
	}
	return (0);
}
