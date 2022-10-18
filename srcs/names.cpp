/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:04:27 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/18 10:41:37 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	names(int socketClient, std::string channelName, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	if (channelMap.find(channelName) != channelMap.end())
	{
		std::string buffer = ":127.0.0.1 353 = " + channelName + " :";
		std::set<int>::iterator user = channelMap.find(channelName)->second.getUserSet().begin();
		std::set<int>::iterator end = channelMap.find(channelName)->second.getUserSet().end();
		while (user != end)
		{
			buffer = buffer + " " + (channelMap.find(channelName)->second.isInOperSet(userMap[*user].getSocket()).first == true ? "@" : "") + userMap[*user].getNickname();
			++user;
		}
		std::cout << BRED << buffer << std::endl;
		sendMsg(socketClient, buffer);
		std::string msg = ":127.0.0.1 366 = " + channelName + " :End of /NAMES list";
		sendMsg(socketClient, msg);
	}
	return (0);
}