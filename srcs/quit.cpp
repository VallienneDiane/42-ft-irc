/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:33:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/21 10:43:45 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	quit(int socketClient, std::string &reason, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User user = userMap[socketClient];
	std::cout << BRED << reason << END << std::endl;
	std::string msg = userSource(userMap[socketClient]) + " " + reason;

	std::map<std::string, Channel>::iterator channel = channelMap.begin();
	std::map<std::string, Channel>::iterator channelEnd = channelMap.end();
	while (channel != channelEnd)
	{
		if (channel->second.isInUserSet(socketClient).first)
		{
			informAllUsers(channel->second.getUserSet(), msg);
			channel->second.delUser(socketClient);
		}
		if (channel->second.isInOperSet(socketClient).first)
			channel->second.delOper(socketClient);
		channel++;
	}
	userMap.erase(socketClient);

	// std::set<std::string>::iterator channel = user.getChannels().begin();
	// std::set<std::string>::iterator channelEnd = user.getChannels().end();
	// while (channel != channelEnd)
	// {
	// 	std::cout << BRED << "PAR ICI 1 " << *channel << std::endl;
	// 	informAllUsers(channelMap.find(*channel)->second.getUserSet(), msg);
	// 	*channel++;
	// 	std::cout << BRED << "PAR LA" << std::endl;
	// }
	std::cout << BRED << "SORTIE" << std::endl;
	// informAllUsers(user.getPrivMsg(), msg);
	
	return (0);
}