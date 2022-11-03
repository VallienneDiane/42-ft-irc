/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:39:50 by amarchal          #+#    #+#             */
/*   Updated: 2022/11/03 15:05:00 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

void	channelInfo(int socketClient, Channel &channel, std::map<int, User> &userMap)
{
	std::cout << "Topic is : " << channel.getTopic() << std::endl;
	std::string buffer = " = " + channel.getName() + " " + channel.userCount() + " :" + channel.getTopic();
	numericReply(RPL_LIST, socketClient, userMap, &buffer);
}

void	list(int socketClient, std::vector<std::string> commands, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::map<std::string, Channel>::iterator channelEnd = channelMap.end();
	if (commands.size() == 2)
	{
		std::vector<std::string> channelNames = splitNames(*(commands.begin() + 1));
		std::vector<std::string>::iterator channelNamesEnd = channelNames.end();
		
		for (std::vector<std::string>::iterator name = channelNames.begin(); name != channelNamesEnd; name++)
		{
			std::map<std::string, Channel>::iterator channel = channelMap.find(*name);
			////// CHECK IF CHANNEL EXISTS
			if (channel != channelEnd)
				channelInfo(socketClient, channel->second, userMap);
			else
				numericReply(ERR_NOSUCHCHANNEL, socketClient, userMap, &(*name));
		}
		numericReply(RPL_LISTEND, socketClient, userMap, NULL);
	}
	else if (commands.size() == 1)
	{
		for (std::map<std::string, Channel>::iterator channel = channelMap.begin(); channel != channelEnd; channel++)
		{
			channelInfo(socketClient, channel->second, userMap);
		}
		numericReply(RPL_LISTEND, socketClient, userMap, NULL);
	}
}