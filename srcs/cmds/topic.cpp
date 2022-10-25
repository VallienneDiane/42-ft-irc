/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:24:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/21 11:11:09 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

bool	topic(int socketClient, std::string channel, std::vector<std::string> topic,std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User								&current = userMap[socketClient];
	std::string							buffer;
	std::vector<std::string>::iterator	it;
	
	for(it = topic.begin() + 2; it != topic.end(); it++) //GET THE TOPIC
	{
		if(it == topic.end() - 1)
			buffer = buffer + (*it);
		else
			buffer = buffer + (*it)+ " ";
	}	
	if (buffer[0] == ':')
		buffer.erase(0,1);
	std::cout << buffer << std::endl;
	if(channelMap.find(channel) != channelMap.end())
	{
		if(channel[0] == '#') //IF CHANNEL BEGIN WITH #
		{
			if(channelMap.find(channel)->second.isInUserSet(socketClient).first == false) //IF USER NOT IN CHANNEL
			{
				numericReply(ERR_NOTONCHANNEL, socketClient, userMap, &(channel));
			}
			else
			{
				if(buffer.empty()) //IF EMPTY STRING, CHANNEL TOPIC HAS TO BE CLEARED
				{
					numericReply(RPL_NOTOPIC, socketClient, userMap, &channel);
					channelMap.find(channel)->second.setTopic(buffer);
				}
				else //SET TOPIC AND INFORM ALL USERS
				{
					unsigned long int sec= time(NULL);
					std::stringstream timestamp;
					timestamp << sec;
					std::string msg = userSource(current) + " TOPIC " + channel + " :" + buffer;
					channelMap.find(channel)->second.setTopic(buffer);
					informAllUsers(channelMap.find(channel)->second.getUserSet(), msg);
					std::string str = " " + userMap[socketClient].getNickname() + " " + channel + " ";
					str += timestamp.str();
					numericReply(RPL_TOPICWHOTIME, socketClient, userMap, &str);
				}
			}
		}
	}
	else
		numericReply(ERR_NOSUCHCHANNEL,socketClient, userMap, &(channel));
	return(0);
}