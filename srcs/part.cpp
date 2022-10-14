/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:21 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/14 17:29:16 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

// MANQUE A GERER LA RAISON DU DEPART DU CHANNEL
// FAIRE FONCTIONNER MESSAGES NUMERIC REPLY
bool	part(int socketClient, std::string channels, std::map<int, User> & userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string> tabChannels = splitNames(channels); //channels table
	std::vector<std::string>::iterator nameChannel = tabChannels.begin(); //iterator on the first channel
	User		&current = userMap[socketClient];
	
	while(nameChannel != tabChannels.end())
	{
		std::cout << "CHANNEL : " << tabChannels[0] << std::endl;
		
		if(channelMap.find(*nameChannel) == channelMap.end()) //if channel doesn't exist
		{
			numericReply(ERR_NOSUCHCHANNEL,socketClient, userMap, nameChannel.base());
			std::cout << RED << "Channel doesn't exist : " << *nameChannel << std::endl;
			break;
		}
		else if(channelMap.find(*nameChannel)->second.getUserList().find(socketClient) 
				== channelMap.find(*nameChannel)->second.getUserList().end()) //if user doesn't belong to this channel
		{
			numericReply(ERR_NOTONCHANNEL, socketClient, userMap, nameChannel.base());
			std::cout << BMAGENTA << "User doesn't belong to this channel : " << *nameChannel << std::endl;
			break;
		}
		std::cout << CYAN << "Erase user of the channel" << *nameChannel << std::endl;
		// std::cout << *nameChannel << "Q\n";
		// std::cout << channelMap.begin()->first << "Q\n";
		channelMap.find(*nameChannel)->second.getUserList().erase(socketClient);
		std::string msg = userSource(current) + " PART :" + *nameChannel;
		sendMsg(socketClient, msg);
		
		// SOLUTIONS POUR DELETE CHAN A TROUVER
		//if no remaining users in channel, delete channel 
		if(channelMap.find(*nameChannel)->second.getUserList().empty()) 
		{
			channelMap.erase(channelMap.find(*nameChannel));
			std::cout << BBLUE << "Erase channel : " << *nameChannel << std::endl;
		}
		nameChannel++;
	}
	return (0);
}