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

void	topic(int socketClient, std::vector<std::string> commands,std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User										&current = userMap[socketClient];
	std::string									buffer;
	std::vector<std::string>::iterator			it;
	std::string channel = commands[1];
	std::vector<std::string> topic = commands;
	std::vector<std::string>::iterator			topicEnd = topic.end();
	std::map<std::string, Channel>::iterator	channelEnd = channelMap.end();

	if (commands.size() == 1) 
	{
        numericReply(ERR_NEEDMOREPARAMS, socketClient, userMap, &commands[0]);
		return ;
    }
	for(it = topic.begin() + 2; it != topicEnd; it++) //GET THE TOPIC
	{
		if(it == topicEnd - 1)
			buffer = buffer + (*it);
		else
			buffer = buffer + (*it)+ " ";
	}	
	if (buffer[0] == ':')
		buffer.erase(0,1);
	if(channelMap.find(channel) != channelEnd)
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
					channelMap.find(channel)->second.setTopic("");
					std::string emptyTopic = userSource(current) + " TOPIC " + channel + " :" + buffer;
					informAllUsers(channelMap.find(channel)->second.getUserSet(), userMap, emptyTopic);
				}
				else //SET TOPIC AND INFORM ALL USERS
				{
					unsigned long int sec= time(NULL);
					std::stringstream timestamp;
					timestamp << sec;
					std::string msg = userSource(current) + " TOPIC " + channel + " :" + buffer;
					channelMap.find(channel)->second.setTopic(buffer);
					informAllUsers(channelMap.find(channel)->second.getUserSet(), userMap, msg);
					std::string str = " " + userMap[socketClient].getNickname() + " " + channel + " ";
					str += timestamp.str();
					numericReply(RPL_TOPICWHOTIME, socketClient, userMap, &str);
				}
			}
		}
	}
	else
		numericReply(ERR_NOSUCHCHANNEL,socketClient, userMap, &(channel));
}