/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:33:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/11/08 11:33:31 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

void	quitAllChannels(int socketClient, std::map<std::string, Channel> &channelMap)
{
	bool emptyChan = false;
	std::string chanToDel;
	std::map<std::string, Channel>::iterator channel = channelMap.begin();
	std::map<std::string, Channel>::iterator channelEnd = channelMap.end();
	while (channel != channelEnd)
	{
		if (channel->second.isInOperSet(socketClient).first)
			channel->second.delOper(socketClient);
		if (channel->second.isInUserSet(socketClient).first)
		{
			channel->second.delUser(socketClient);
			if (channel->second.getUserSet().empty())
			{
				emptyChan = true;
				chanToDel = channel->second.getName();
			}
		}
		channel++;
		if (emptyChan)
		{
			channelMap.erase(chanToDel);
			emptyChan = false;
		}
	}
}

bool	quit(int socketClient, std::string &reason, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::cout << BRED << reason << END << std::endl;
	std::string msg = userSource(userMap[socketClient]) + " " + reason;

	userMap.erase(socketClient);
	std::map<int, User>::iterator user = userMap.begin();
	std::map<int, User>::iterator userEnd = userMap.end();
	while (user != userEnd)
	{
		user->second.addMsgToBuffer(msg);
		user++;
	}
	quitAllChannels(socketClient, channelMap);
	close(socketClient);
	return (1);
}