/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/19 14:01:55 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

//RPL_TOPICWHOTIME a implementer. 
//Sent to a client to let them know who set the topic (<nick>) 
// and when they set it (<setat> is a unix timestamp). Sent after RPL_TOPIC (332).

bool	topic(int socketClient, std::string channel, std::vector<std::string> topic,std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User								&current = userMap[socketClient];
	std::string							buffer;
	std::vector<std::string>::iterator	it;
	// std::vector<std::string>::iterator	nameChannel = tabChannels.begin();
	
	for(it = topic.begin() + 2; it != topic.end(); it++) //GET THE TOPIC
		buffer = buffer + (*it) + " ";
		
	std::cout << "CHAN " << channel << std::endl;
	std::cout << "BUFFER " << buffer << std::endl;

	if(channelMap.find(channel) != channelMap.end())
	{
		if(channel.front() == '#') //IF CHANNEL BEGIN WITH #
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
	}
	else
		numericReply(ERR_NOSUCHCHANNEL,socketClient, userMap, &(channel));
	return(0);
}