/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:27:15 by amarchal          #+#    #+#             */
/*   Updated: 2022/11/08 11:45:44 by amarchal         ###   ########.fr       */
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

void	changeOperStatus(User &user, Channel &channel, char sign, std::map<int, User> &userMap, User &oper)
{
	std::string msg = userSource(oper) + " MODE " + channel.getName();
	if (sign == '+')
	{
		if (channel.isInOperSet(user).first == false)
			channel.addOper(user.getSocket());
		informAllUsers(channel.getUserSet(), userMap, msg + " +o " + user.getNickname());
	}
	if (sign == '-')
	{
		if (channel.isInOperSet(user).first == true)
			channel.delOper(user.getSocket());
		informAllUsers(channel.getUserSet(), userMap, msg + " -o " + user.getNickname());
	}
}

void	mode(int socketClient, std::vector<std::string> commands, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	if (commands.size() == 4)
	{
		std::vector<std::string>::iterator it = commands.begin();
		std::string channelName = *(++it);
		std::map<std::string, Channel>::iterator channelEnd = channelMap.end();
		std::map<int, User>::iterator userEnd = userMap.end();
		std::string mode = *(++it);
		std::string target = *(++it);

		/////// CHECK IF CHANNEL EXIST
		if (channelMap.find(channelName) != channelEnd)
		{
			Channel *channel = &(channelMap.find(channelName)->second);
			/////// CHECK IF USER IS IN CHANNEL AND IS OPER
			if (channel->isInUserSet(socketClient).first && channel->isInOperSet(socketClient).first)
			{
				///////// CHECK IF MODE IS CORRECT
				if (checkMode(mode) == true)	
				{
					//////// CHECK IF TARGET EXIST
					for (std::map<int, User>::iterator user = userMap.begin(); user != userEnd; user++)
					{
						if (user->second.getNickname().compare(target) == 0)
						{
							//////// CHECK IF TARGET IS IN CHANNEL
							if (channel->isInUserSet(user->second.getSocket()).first == true)
							{
								changeOperStatus(user->second, channelMap.find(channelName)->second, mode[0], userMap, userMap[socketClient]);
								return ;	
							}
						}
					}
					numericReply(401, socketClient, userMap, &target);
				}
				else
					numericReply(ERR_UMODEUNKNOWNFLAG, socketClient, userMap, &mode);
					
			}
			else
				numericReply(ERR_CHANOPRIVSNEEDED, socketClient, userMap, &channelName);
		}
		else
			numericReply(403, socketClient, userMap, &channelName);
	}
}