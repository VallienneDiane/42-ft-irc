/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:04:27 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/19 11:48:22 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

void	names(int socketClient, std::string channelName, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::map<std::string, Channel>::iterator channelEnd = channelMap.end();

	if (channelMap.find(channelName) != channelEnd)
	{
		std::string buffer = ":127.0.0.1 353 = " + channelName + " :";
		std::set<int>::iterator user = channelMap.find(channelName)->second.getUserSet().begin();
		std::set<int>::iterator end = channelMap.find(channelName)->second.getUserSet().end();
		while (user != end)
		{
			buffer = buffer + " " + (channelMap.find(channelName)->second.isInOperSet(userMap[*user].getSocket()).first == true ? "@" : "") + userMap[*user].getNickname();
			++user;
		}
		userMap[socketClient].addMsgToBuffer(buffer);
		std::string msg = ":127.0.0.1 366 = " + channelName + " :End of /NAMES list";
		userMap[socketClient].addMsgToBuffer(msg);
	}
}