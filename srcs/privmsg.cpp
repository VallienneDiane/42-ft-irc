/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:41:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/19 11:22:53 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

void	msgToChannel(int socketClient, Channel &channel, fd_set *writeSockets, std::map<int, User> &userMap, std::vector<std::string>::iterator msgBegin, std::vector<std::string>::iterator msgEnd)
{
	std::string buffer = userSource(userMap[socketClient]) + " PRIVMSG " + channel.getName();
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

void	msgToUser(int socketClient, User &user, fd_set *writeSockets, std::map<int, User> &userMap, std::vector<std::string>::iterator msgBegin, std::vector<std::string>::iterator msgEnd, bool firstMsg)
{
	std::string buffer = userSource(userMap[socketClient]) + " PRIVMSG " + user.getNickname();
	while (msgBegin != msgEnd)
		buffer = buffer + " " + *msgBegin++;
	////////// CHECK IF USER SOCKET IS READY FOR WRITING
	if (FD_ISSET(user.getSocket(), writeSockets) && user.getSocket() != socketClient)
		sendMsg(user.getSocket(), buffer);
	if (firstMsg)
		sendMsg(socketClient, buffer);
	
}

void	linkUsers(int socketClient, int socketUser, std::map<int, User> &userMap)
{
	userMap[socketClient].addPrivMsg(socketUser);
	userMap[socketUser].addPrivMsg(socketClient);
}

bool	privmsg(int socketClient, std::vector<std::string> msg, fd_set *writeSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string>::iterator it = msg.begin();
	std::vector<std::string>::iterator msgEnd = msg.end();
	it++;
	
	/////////// SEND MSG TO CHANNEL
	if ((*it)[0] == '#')
	{
		/////////// CHECK IF CHANNEL EXIST
		if (channelMap.find(*it) != channelMap.end())
		{
			/////////// CHECK IF USER IS IN CHANNEL
			if (channelMap.find(*it)->second.isInUserSet(socketClient).first)
				msgToChannel(socketClient, channelMap.find(*it)->second, writeSockets, userMap, ++it, msgEnd);
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
				{
					linkUsers(socketClient, user->second.getSocket(), userMap);
					msgToUser(socketClient, user->second, writeSockets, userMap, ++it, msgEnd, true);
				}
				else
					msgToUser(socketClient, user->second, writeSockets, userMap, ++it, msgEnd, false);
				return (0);
			}
		}
		/////////// IF USER DOES NOT EXIST
		numericReply(401, socketClient, userMap, &(*it));
	}
	return (0);
}
