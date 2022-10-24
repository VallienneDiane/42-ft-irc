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

#include "../incs/ircserv.hpp"

void	msgToChannel(int socketClient, Channel &channel, fd_set *writeSockets, std::map<int, User> &userMap, std::vector<std::string>::iterator msgBegin, std::vector<std::string>::iterator msgEnd, int type)
{
	std::string buffer;
	std::cerr << "chan name = " << channel.getName() << std::endl;
	if (type == 1)
		buffer = userSource(userMap[socketClient]) + " PRIVMSG " + channel.getName();
	else
		buffer = userSource(userMap[socketClient]) + " NOTICE " + channel.getName();
	while (msgBegin != msgEnd)
		buffer = buffer + " " + *msgBegin++;

	///////// FOR EACH USER IN THE CHANNEL
	for (std::set<int>::iterator channelUser = channel.getUserSet().begin(); channelUser != channel.getUserSet().end(); channelUser++)
	{
		////////// CHECK IF USER SOCKET IS READY FOR WRITING
		if (FD_ISSET(*channelUser, writeSockets) && *channelUser != socketClient)
			sendMsg(*channelUser, buffer);
	}
}

void	msgToUser(int socketClient, User &user, fd_set *writeSockets, std::map<int, User> &userMap, std::vector<std::string>::iterator msgBegin, std::vector<std::string>::iterator msgEnd, int type)
{
	std::string buffer;
	if (type == 1)
		buffer = userSource(userMap[socketClient]) + " PRIVMSG " + user.getNickname();
	else if (type == 2)
		buffer = userSource(userMap[socketClient]) + " NOTICE " + user.getNickname();
	while (msgBegin != msgEnd)
		buffer = buffer + " " + *msgBegin++;
	////////// CHECK IF USER SOCKET IS READY FOR WRITING
	if (FD_ISSET(user.getSocket(), writeSockets) && user.getSocket() != socketClient)
		sendMsg(user.getSocket(), buffer);
	sendMsg(socketClient, buffer);
	
}

void	linkUsers(int socketClient, int socketUser, std::map<int, User> &userMap)
{
	userMap[socketClient].addPrivMsg(socketUser);
	userMap[socketUser].addPrivMsg(socketClient);
}

bool	privmsg(int socketClient, std::vector<std::string> msg, fd_set *writeSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap, int type)
{
	std::vector<std::string>::iterator it = msg.begin();
	std::vector<std::string>::iterator msgEnd = msg.end();
	it++;
	
	/////////// SEND MSG TO CHANNEL
	if ((*it)[0] == '#')
	{
		std::map<std::string, Channel>::iterator chanIt = channelMap.find(*it);
		/////////// CHECK IF CHANNEL EXIST
		if (chanIt != channelMap.end())
		{
			/////////// CHECK IF USER IS IN CHANNEL
			if (chanIt->second.isInUserSet(socketClient).first)
				msgToChannel(socketClient, chanIt->second, writeSockets, userMap, ++it, msgEnd, type);
		}
		else
			numericReply(403, socketClient, userMap, &(*it));
	}
	/////////// SEND MSG TO USER
	else
	{
		/////////// CHECK IF USER EXIST
		for (std::map<int, User>::iterator user = userMap.begin(); user != userMap.end(); user++)
		{
			if (user->second.getNickname() == *it)
			{
				//////////// ADD USER IN CONTACT LIST IF NOT ALLREADY IN IT
				if (userMap[socketClient].isInPrivMsg(user->second.getSocket()) == false)
					linkUsers(socketClient, user->second.getSocket(), userMap);
				msgToUser(socketClient, user->second, writeSockets, userMap, ++it, msgEnd, type);
				return (0);
			}
		}
		/////////// IF USER DOES NOT EXIST
		numericReply(401, socketClient, userMap, &(*it));
	}
	return (0);
}
