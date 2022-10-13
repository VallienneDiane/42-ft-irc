/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:21 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 18:30:51 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

// HAVE TO SAY TO CLIENT THAT USER HAS BEEN EJECTED FROM CHANNEL !!!!

bool	part(int socketClient, std::string channels, std::map<int, User> & userMap, std::map<std::string, Channel> &channelMap)
{
	std::vector<std::string> channelNames = splitNames(channels);
	std::vector<std::string>::iterator channelName = channelNames.begin();
	while (channelName != channelNames.end()) //parcours vector de channels
	{
		if(channelMap.find(*channelName) == channelMap.end()) //si channel n'existe pas renvoie error
		{
			std::cout << "si channel existe pas" << std::endl;
			numericReply(ERR_NOSUCHCHANNEL,socketClient, *channelName, userMap);
		}
		else if(channelMap.find(*channelName)->second.getUserList().find(socketClient)
					 ==  channelMap.find(*channelName)->second.getUserList().end()) //si user pas dans channel mais que channel existe
		{
			std::cout << "si channel existe mais user pas dedans" << std::endl;
			numericReply(ERR_NOSUCHCHANNEL, socketClient, *channelName, userMap);
		}
		else
		{
			std::cout << "erase user" << std::endl;
			channelMap.find(*channelName)->second.getUserList().erase(socketClient);
			std::string msg = userMap[socketClient].getNickname();
			if(channelNames.begin() == channelNames.end()) //si quitte un seul channel
			{
				msg += "leave channel \" ";
				msg += *channelName;
				msg += " \"";
				sendMsg(socketClient, msg);
			}
			else
			{
				msg += "leave channels \" ";
				while(channelMap.find(*channelName) != channelMap.end())
				{
					msg += *channelName;
					msg += " and \"";
				}
				sendMsg(socketClient, msg);
			}
		}
	}
	(void)socketClient;
	(void)userMap;
	(void)channelMap;
	return (0);
}