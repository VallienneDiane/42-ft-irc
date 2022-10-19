/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/18 14:00:49 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

//dans join, ajouter RPL_TOPIC : quand new user dans chan, phrase qui dit le topic actuel
bool	topic(int socketClient, std::string channel, std::vector<std::string> topic,std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User		&current = userMap[socketClient];
	std::vector<std::string>::iterator	it;
	std::string	buffer;
	
	for(it = topic.begin() + 2; it != topic.end(); it++) //GET NEW TOPIC
		buffer = buffer + (*it) + " ";
	// std::cout << "CHAN " << channel << std::endl;
	// std::cout << "BUFFER " << buffer << std::endl;
	if(channel[0] == '#' && channelMap.find(channel) == channelMap.end())
	{
		if(channelMap.find(channel)->second.isInUserSet(socketClient).first == false)
		{
			std::cout << MAGENTA << "user not in channel" << std::endl;
			numericReply(ERR_NOTONCHANNEL, socketClient, userMap, &(channel));
		}
		else
		{
			if(topic.empty())
			{
				std::cout << BLUE << "empty topic" << std::endl;
				numericReply(RPL_NOTOPIC, socketClient, userMap, &(channel));
			}
			else
			{
				std::string msg = userSource(current) + " TOPIC " + channel + " " + buffer;
				sendMsg(socketClient, msg);
			}
		}
	}
	return(0);
}