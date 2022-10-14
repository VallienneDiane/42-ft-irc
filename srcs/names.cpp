/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:04:27 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/14 16:33:26 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	names(int socketClient, std::string channelName, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	if (channelMap.find(channelName) != channelMap.end())
	{
		std::map<int, User>::iterator user = channelMap.find(channelName)->second.getUserList().begin();
		std::map<int, User>::iterator end = channelMap.find(channelName)->second.getUserList().end();
		
		std::string buffer = ":127.0.0.1 353 = " + channelName + " :";
		
		while (user != end)
		{
			// std::string msg = /*userMap.find(socketClient)->second.getNickname() +*/ ":127.0.0.1 353 = " + channelName + " :" + user->second.getNickname();
			// std::cout << MAGENTA << msg << END << std::endl;
			// sendMsg(socketClient, msg);
			buffer = buffer + " @" + user->second.getNickname();
			++user;
		}
		sendMsg(socketClient, buffer);
		std::cout << MAGENTA << buffer << END << std::endl;
		std::string msg = /*channelMap.find(channelName)->second.getUserList().find(socketClient)->second.getNickname() +*/ ":127.0.0.1 366 = " + channelName + " :End of /NAMES list";
		std::cout << MAGENTA << msg << END << std::endl;
		// std::cout << MAGENTA << msg << END << std::endl;
		sendMsg(socketClient, msg);
	}
	return (0);
	(void)userMap;
}