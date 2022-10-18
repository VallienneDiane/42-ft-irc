/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:28:26 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/18 14:04:24 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

std::vector<std::string> splitNames(std::string &names)
{
	std::string tmp = names;
	std::stringstream ss(names);
	std::vector<std::string> result;
	while (getline(ss, tmp, ','))
		result.push_back(tmp);
	return (result);
}

void	informAllUsers(std::set<int> userSet, std::string msg, std::string channelName, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::set<int>::iterator user = userSet.begin();
	std::set<int>::iterator userEnd = userSet.end();
	while (user != userEnd)
	{
		sendMsg(*user, msg);
		names(*user, channelName, userMap, channelMap);
		user++;
	}
}

bool	join(int socketClient, std::string &channelNames, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string> chanNames = splitNames(channelNames);
	std::vector<std::string>::iterator name = chanNames.begin();
	std::vector<std::string>::iterator end = chanNames.end();
	while (name != end)
	{
		if (name->front() != '#')			////////// ADD # IN FRONT OF CHANNEL NAME IF NOT PRESENT
			name->insert(0, 1, '#');
		//////////// NEW CHANNEL
		if (channelMap.find(*name) == channelMap.end())
		{
			Channel newChannel(*name, userMap[socketClient]);								///////// CREATE NEW CHANNEL WITH ITS NAME AND OPERATOR
			channelMap.insert(std::pair<std::string, Channel>(*name, newChannel));			///////// INSERT NEW CHANNEL INTO CHANNELMAP
			channelMap.find(*name)->second.addUser(socketClient);				 //////////// ADD USER SOCKET IN CHANNEL'S USERSET
			std::string msg = ":" + userMap[socketClient].getNickname() + " JOIN :" + *name;
			informAllUsers(channelMap.find(*name)->second.getUserSet(), msg, *name, userMap, channelMap);
		}
		//////////// EXISTING CHANNEL
		else
		{
			//////////// CLIENT ALREADY IN THIS CHANNEL
			// if (channelMap.find(*name)->second.getUserList().find(socketClient) != channelMap.find(*name)->second.getUserList().end())
			// if (channelMap.find(*name)->second.getUserSet().find(socketClient) != channelMap.find(*name)->second.getUserSet().end())
			if (channelMap.find(*name)->second.isInUserSet(socketClient).first)
			{
				
			}
			//////////// CLIENT NOT IN THIS CHANNEL
			else
			{
				channelMap.find(*name)->second.addUser(socketClient);				 //////////// ADD USER SOCKET IN CHANNEL'S USERSET
				std::string msg = ":" + userMap[socketClient].getNickname() + " JOIN :" + *name;
				informAllUsers(channelMap.find(*name)->second.getUserSet(), msg, *name, userMap, channelMap);
			}
		}
		name++;	
	}
	return (0);
}