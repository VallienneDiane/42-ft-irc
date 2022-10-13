/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:04:27 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/13 18:32:18 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	names(int socketClient, std::string channelName, std::map<int, User> userMap, std::map<std::string, Channel> channelMap)
{
	// std::cout << BRED << "ici" << END << std::endl;
	// if (channelMap.find(channelName) != channelMap.end())
	// {
	// 	std::cout << RED << "la" << END << std::endl;
	// 	std::map<int, User>::iterator user = channelMap.find(channelName)->second.getUserList().begin();
	// 	std::map<int, User>::iterator end = channelMap.find(channelName)->second.getUserList().end();
		
	// 	while (user != end)
	// 	{
	// 		std::string msg = userMap.find(socketClient)->second.getNickname() + " = " + channelName + " :" + user->second.getUsername();
	// 		std::cout << GREEN << "yo" << END << std::endl;
	// 		std::cout << MAGENTA << msg << END << std::endl;
	// 		sendMsg(socketClient, msg);
	// 		user++;
	// 	}
	// 	std::string msg = channelMap.find(channelName)->second.getUserList().find(socketClient)->second.getNickname() + " " + channelName + " :End of /NAMES list";
	// 	std::cout << MAGENTA << msg << END << std::endl;
	// 	sendMsg(socketClient, msg);
	// }
	(void)socketClient;
	(void)channelName;
	(void)channelMap;
	(void)userMap;
	return (0);
}