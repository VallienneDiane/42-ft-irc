/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/19 13:49:27 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

//dans join, ajouter RPL_TOPIC : quand new user dans chan, phrase qui dit le topic actuel
bool	topic(int socketClient, std::string channel, std::vector<std::string> topic,std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User								&current = userMap[socketClient];
	std::string							buffer;
	std::vector<std::string>::iterator	it;
	
	for(it = topic.begin() + 2; it != topic.end(); it++) //GET THE TOPIC
		buffer = buffer + (*it) + " ";
		
	std::cout << "CHAN " << channel << std::endl;
	std::cout << "BUFFER " << buffer << std::endl;

	if(channel.front() == '#') //&& channelMap.find(channel) == channelMap.end()//IF CHANNEL EXIST AND BEGIN WITH #
	{
		
		if(channelMap.find(channel)->second.isInUserSet(socketClient).first == false) //IF USER NOT IN CHANNEL
		{
			std::cout << MAGENTA << "user not in channel" << std::endl;
			numericReply(ERR_NOTONCHANNEL, socketClient, userMap, &(channel));
		}
		else
		{
			if(buffer.empty()) //IF EMPTY STRING, CHANNEL TOPIC HAS TO BE CLEARED
			{
				// std::cout << MAGENTA << "empty topic" << std::endl;
				numericReply(RPL_NOTOPIC, socketClient, userMap, &channel);
				channelMap.find(channel)->second.setTopic(buffer);
			}
			else //SET TOPIC AND INFORM ALL USERS
			{
				// std::cout << RED << "set topic" << std::endl;
				std::string msg = userSource(current) + " TOPIC " + channel + " " + buffer;
				channelMap.find(channel)->second.setTopic(buffer);
				informAllUsers(channelMap.find(channel)->second.getUserSet(), msg);
			}
		}
	}
	return(0);
}