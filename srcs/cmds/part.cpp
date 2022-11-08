/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:21 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/21 11:10:57 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

void	part(int socketClient, std::vector<std::string> commands, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User										&current = userMap[socketClient];
	std::string channels = commands[1];
	std::vector<std::string> reason = commands;
	std::vector<std::string>					tabChannels = splitNames(channels);
	std::vector<std::string>::iterator			nameChannel = tabChannels.begin();
	std::string 								buffer;
	std::vector<std::string>::iterator			it;
	std::vector<std::string>::iterator 			reasonEnd = reason.end();
	std::map<std::string, Channel>::iterator 	channelEnd = channelMap.end();
	std::vector<std::string>::iterator			tabChannelsEnd = tabChannels.end();
	
	if (commands.size() < 2) 
	{
        numericReply(ERR_NEEDMOREPARAMS, socketClient, userMap, &commands[0]);
		return ;
    }
	for(it = reason.begin() + 2; it != reasonEnd; it++) //GET REASON FOR LEAVING CHAN
		buffer = buffer + (*it) + " ";
	if (buffer.empty())
		buffer = "no reason given";
	while(nameChannel != tabChannelsEnd)
	{
		if((*nameChannel)[0] == '#') //IF FIRST LETTER OF CHAN IS #
		{
			if(channelMap.find(*nameChannel) == channelEnd)//IF CHANNEL DOESN'T EXIST
				numericReply(ERR_NOSUCHCHANNEL,socketClient, userMap, &(*nameChannel)); //err 403
			else //IF CHANNEL EXIST
			{
				if(channelMap.find(*nameChannel)->second.isInUserSet(socketClient).first == false) //IF USER DOESN'T BELONG TO THIS CHAN
					numericReply(ERR_NOTONCHANNEL, socketClient, userMap, &(*nameChannel)); //err 442
				else
				{
					std::string msg = userSource(current) + " PART " + *nameChannel + " " + buffer;
					informAllUsers(channelMap.find(*nameChannel)->second.getUserSet(), userMap, msg);
					channelMap.find(*nameChannel)->second.delUser(socketClient); //DO PART CMD (ERASE USER OF CHAN)
					if(channelMap.find(*nameChannel)->second.isInOperSet(socketClient).first)
						channelMap.find(*nameChannel)->second.delOper(socketClient);
					if(channelMap.find(*nameChannel)->second.getUserSet().empty()) //IF NO USER LEFT, DELETE CHAN
						channelMap.erase(*nameChannel);
				}
			} 
		}
		nameChannel++;
	}
}
