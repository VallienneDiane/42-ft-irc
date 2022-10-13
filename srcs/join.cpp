/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:28:26 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/13 15:44:30 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

static std::vector<std::string> splitNames(std::string names)
{
	std::string tmp = names;
	std::stringstream ss(names);
	std::vector<std::string> result;
	while (getline(ss, tmp, ','))
	{
		result.push_back(tmp);
	}
	return (result);
}

bool	join(int socketClient, const std::string &channelName, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string> names = splitNames(channelName);
	std::vector<std::string>::iterator name = names.begin();
	while (name != names.end())
	{
		//////////// NEW CHANNEL
		if (channelMap.find(*name) == channelMap.end())
		{
			Channel newChannel(*name, userMap[socketClient]);
			channelMap.insert(std::pair<std::string, Channel>(*name, newChannel));
			channelMap.find(*name)->second.getUserList()[socketClient];
			std::string msg = ":" + userMap[socketClient].getNickname() + " JOIN :" + *name;
			sendMsg(socketClient, msg);
		}
		//////////// EXISTING CHANNEL
		else
		{
			//////////// CLIENT ALREADY IN THIS CHANNEL
			if (channelMap.find(*name)->second.getUserList().find(socketClient) != channelMap.find(*name)->second.getUserList().end())
			{
				
			}
			//////////// CLIENT NOT IN THIS CHANNEL
			else
			{
				channelMap.find(*name)->second.getUserList()[socketClient];
				std::string msg = ":" + userMap[socketClient].getNickname() + " JOIN :" + *name;
				sendMsg(socketClient, msg);
				
			}
		}
		name++;	
	}
	return (0);
}