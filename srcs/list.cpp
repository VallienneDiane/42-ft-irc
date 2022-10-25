/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:39:50 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/25 14:30:50 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

void	channelInfo(int socketClient, Channel &channel, std::map<int, User> &userMap)
{
	std::cout << "Topic is : " << channel.getTopic() << std::endl;
	std::string buffer = " = " + channel.getName() + " " + channel.userCount() + channel.getTopic();
	numericReply(322, socketClient, userMap, &buffer);
}

void	list(int socketClient, std::vector<std::string> commands, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	if (commands.size() == 2)
	{
		std::vector<std::string> channelNames = splitNames(*(commands.begin() + 1));
		std::vector<std::string>::iterator channelNamesEnd = channelNames.end();
		for (std::vector<std::string>::iterator name = channelNames.begin(); name != channelNamesEnd; name++)
		{
			std::map<std::string, Channel>::iterator channel = channelMap.find(*name);
			////// CHECK IF CHANNEL EXISTS
			if (channel != channelMap.end())
				channelInfo(socketClient, channel->second, userMap);
			else
				numericReply(403, socketClient, userMap, &(*name));
		}
	}
	else if (commands.size() == 1)
	{
		std::map<std::string, Channel>::iterator channelEnd = channelMap.end();
		for (std::map<std::string, Channel>::iterator channel = channelMap.begin(); channel != channelEnd; channel++)
		{
			channelInfo(socketClient, channel->second, userMap);
		}
	}
	numericReply(323, socketClient, userMap, nullptr);
}