/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:28:26 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/21 10:43:10 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

std::vector<std::string> splitNames(std::string &names)
{
	std::string tmp = names;
	std::stringstream ss(names);
	std::vector<std::string> result;
	while (getline(ss, tmp, ','))
		result.push_back(tmp);
	return (result);
}

void	informAllUsers(std::set<int> userSet, std::map<int, User> &userMap, std::string msg)
{
	std::set<int>::iterator user = userSet.begin();
	std::set<int>::iterator userEnd = userSet.end();
	while (user != userEnd)
	{
		userMap[*user].addMsgToBuffer(msg);
		user++;
	}
}

void	join(int socketClient, std::vector<std::string> &command, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	if (command.size() < 2)
	{
		numericReply(ERR_NEEDMOREPARAMS, socketClient, userMap, &command[0]);
		return ;
	}
	std::vector<std::string>	chanNames = splitNames(command[1]);
	std::vector<std::string>::iterator pass;
	std::vector<std::string>::iterator passEnd;
	std::vector<std::string> chanPass;
	if (command.size() >= 3)
	{
		chanPass = splitNames(command[2]);
		pass = chanPass.begin();
		passEnd = chanPass.end();
	}
	std::vector<std::string>::iterator name = chanNames.begin();
	std::vector<std::string>::iterator nameEnd = chanNames.end();
	std::map<std::string, Channel>::iterator channelEnd = channelMap.end();
	while (name != nameEnd)
	{
		if ((*name)[0] != '#')			////////// ADD # IN FRONT OF CHANNEL NAME IF NOT PRESENT
			name->insert(0, 1, '#');
		//////////// NEW CHANNEL
		if (channelMap.find(*name) == channelEnd)
		{
			Channel newChannel(*name, userMap[socketClient]);								///////// CREATE NEW CHANNEL WITH ITS NAME AND OPERATOR
			channelMap.insert(std::pair<std::string, Channel>(*name, newChannel));			///////// INSERT NEW CHANNEL INTO CHANNELMAP
			channelMap.find(*name)->second.addUser(socketClient);				 			///////// ADD USER SOCKET IN CHANNEL'S USERSET
			if (command.size() >= 3 && pass != passEnd)
				channelMap.find(*name)->second.setKey(*pass);
			userMap[socketClient].addChannel(*name);										///////// ADD CHANNEL TO THE LIST OF CHANNELS THE USER IS ON
			std::string msg = ":" + userMap[socketClient].getNickname() + " JOIN :" + *name;
			informAllUsers(channelMap.find(*name)->second.getUserSet(), userMap, msg);
			names(socketClient, *name, userMap, channelMap);
		}
		//////////// EXISTING CHANNEL
		else
		{
			Channel *currentChan = &channelMap.find(*name)->second;
			//////////// CLIENT NOT IN THIS CHANNEL
			if (currentChan->isInUserSet(socketClient).first == false)
			{	
				if ((currentChan->hasKey() && command.size() >= 3 && pass != passEnd && currentChan->getKey().compare(*pass) == 0) || currentChan->hasKey() == false)
				{
					currentChan->addUser(socketClient);				 //////////// ADD USER SOCKET IN CHANNEL'S USERSET
					userMap[socketClient].addChannel(*name);										///////// ADD CHANNEL TO THE LIST OF CHANNELS THE USER IS ON
					std::string msg = ":" + userMap[socketClient].getNickname() + " JOIN :" + *name;
					informAllUsers(currentChan->getUserSet(), userMap, msg);
					names(socketClient, *name, userMap, channelMap);
					std::string topic = *name + " " + *name + " " + currentChan->getTopic() ;
					if (currentChan->getIsTopicSet() == true)
					{
						std::cout << GREEN << "YES " << std::endl;
						numericReply(RPL_TOPIC, socketClient, userMap, &topic);
					}
				}
				else
					numericReply(ERR_BADCHANNELKEY, socketClient, userMap, &(*name));
			}
		}
		if (command.size() >= 3 && pass != passEnd)
			pass++;
		name++;	
	}
}