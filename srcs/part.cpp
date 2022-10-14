/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:21 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/14 14:10:01 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	part(int socketClient, std::string channels, std::map<int, User> & userMap, std::map<std::string, Channel> &channelMap)
{
	std::cout << "CHANNELS : " << channels << std::endl;
	std::vector<std::string> tabChannels = splitNames(channels); //tableau des noms de channels
	std::vector<std::string>::iterator nameChannel = tabChannels.begin(); //le nom du premier channel
	std::map<int, User> usersList = channelMap.find(*nameChannel)->second.getUserList(); //acces la liste des users
	
	while(nameChannel != tabChannels.end())
	{
		nameChannel->erase(0,1);
		std::cout << "NAME CHANNEL " << *nameChannel << std::endl;
		nameChannel++;
	}
	while (nameChannel != tabChannels.end()) //parcours vector
	{
		std::cout << "CHANNEL[0] : " << tabChannels[0] << std::endl;
		std::cout << "NOM CHANNEL : " << *nameChannel << std::endl;
		if(channelMap.find(*nameChannel) == channelMap.end()) //si channel n'existe pas renvoie error
		{
			std::cout << "si channel existe pas" << std::endl;
			numericReply(ERR_NOSUCHCHANNEL,socketClient, userMap, nameChannel.base());
			return (1);
		}
		else if(usersList.find(socketClient) == usersList.end()) //si user pas dans channel mais que channel existe
		{
			std::cout << "si channel existe mais user pas dedans" << std::endl;
			numericReply(ERR_NOSUCHCHANNEL, socketClient, userMap, nameChannel.base());
			return (1);
		}
		channelMap.find(*nameChannel)->second.getUserList().erase(socketClient);
		std::cout << "erase user of the channel" << std::endl;
		std::string msg;
		msg = userMap[socketClient].getNickname();
		msg += " is leaving the channel #POUET";
		sendMsg(socketClient, msg);
		// if(channelMap.find(*nameChannel)->second.getUserList().empty()) // si pas de users dans channel, efface channel
		// {
		// 	std::cout << "erase channel" << std::endl;
		// 	channelMap.erase(channelMap.find(*nameChannel));
		// 	return (0);
		// }
	}
	std::cout << "end function part" << std::endl;
	return (0);
}