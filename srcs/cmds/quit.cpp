/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:33:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/11/03 14:25:44 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

void	quit(int socketClient, std::string &reason, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
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

	std::set<int>::iterator	friendBegin = user.getPrivMsg().begin();
	std::set<int>::iterator	friendEnd = user.getPrivMsg().end();
	while (friendBegin != friendEnd) {
		sendMsg(*friendBegin, msg);
		userMap[*friendBegin].removePrivMsg(socketClient);
		++friendBegin;
	}
}