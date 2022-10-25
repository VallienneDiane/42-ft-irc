/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:27:15 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/25 16:42:45 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

bool	checkMode(std::string &mode)
{
	if (mode.size() != 2)
		return (false);
	if ((mode[0] != '+' && mode[0] != '-') || mode[1] != 'o')
		return (false);
	return (true);
}

void	changeOperStatus(User &user, Channel &channel, char sign)
{
	if (sign == '+')
	{
		if (channel.isInOperSet(user).first == false)
			channel.addOper(user.getSocket());
	}
	if (sign == '-')
	{
		if (channel.isInOperSet(user).first == true)
			channel.delOper(user.getSocket());
	}
}

void	mode(int socketClient, std::vector<std::string> commands, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	if (commands.size() == 4)
	{
		std::vector<std::string>::iterator it = commands.begin();
		std::string channelName = *(++it);
		std::string mode = *(++it);
		std::string target = *(++it);

		/////// CHECK IF CHANNEL EXIST
		if (channelMap.find(channelName) != channelMap.end())
		{
			Channel *channel = &(channelMap.find(channelName)->second);
			/////// CHECK IF USER IS IN CHANNEL AND IS OPER
			if (channel->isInUserSet(socketClient).first && channel->isInOperSet(socketClient).first)
			{
				///////// CHECK IF MODE IS CORRECT
				if (checkMode(mode) == true)	
				{
					//////// CHECK IF TARGET EXIST
					for (std::map<int, User>::iterator user = userMap.begin(); user != userMap.end(); user++)
					{
						if (user->second.getNickname().compare(target) == 0)
						{
							//////// CHECK IF TARGET IS IN CHANNEL
							if (channel->isInUserSet(user->second.getSocket()).first == true)
							{
								changeOperStatus(user->second, channelMap.find(channelName)->second, mode[0]);
								return ;	
							}
						}
					}
					numericReply(401, socketClient, userMap, &target);
				}
			}
		}
		else
			numericReply(403, socketClient, userMap, &channelName);
	}
}