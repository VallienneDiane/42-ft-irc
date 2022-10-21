/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:33:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/19 13:38:00 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	quit(int socketClient, std::string &reason, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	User user = userMap[socketClient];
	std::cout << BRED << reason << END << std::endl;
	std::string msg = userSource(userMap[socketClient]) + " " + reason;
	
	std::set<std::string>::iterator channel = user.getChannels().begin();
	std::set<std::string>::iterator channelEnd = user.getChannels().end();
	while (channel != channelEnd)
	{
		informAllUsers(channelMap.find(*channel)->second.getUserSet(), msg);
		channel++;
	}
	// informAllUsers(user.getPrivMsg(), msg);
	
	return (0);
}