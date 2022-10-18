/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:58:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/17 16:58:23 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

std::string	buildReason(const std::vector<std::string> &tab)
{
	std::string	reason;
	size_t sizeTab = tab.size();
	for (size_t i = 4; i < sizeTab; ++i)
	{
		if (!reason.empty())
			reason += " ";
		reason += tab[i];
	}
	return reason;
}

void	notHereUser(int socketClient, std::map<int, User> userMap, const std::string &nickname, const std::string &channel)
{
	std::string	context = nickname;
	context += ' ';
	context += channel;
	numericReply(ERR_USERNOTINCHANNEL, socketClient, userMap, &context);
}

void	kickOneByOne(const User &kicker, const User &toKick, const std::string &reason, Channel &chan)
{
	std::string	response = userSource(kicker);
	std::set<int>::iterator	end = chan.getUserSet().end();

	response += " KICK ";
	response += chan.getName();
	response += " ";
	response += toKick.getNickname();
	if (!reason.empty()) {
		response += " ";
		response += reason;
	}
	for (std::set<int>::iterator it = chan.getUserSet().begin(); it != end; ++it)
		sendMsg(*it, response);
	chan.delUser(toKick.getSocket());
	if (chan.isInOperSet(toKick.getSocket()).first)
		chan.delOper(toKick.getSocket());
}

void	kick(int socketClient, std::vector<std::string> &command, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	if (command.size() < 3)
	{
		numericReply(ERR_NEEDMOREPARAMS , socketClient, userMap, &command[0]);
		return ;
	}
	std::map<std::string, Channel>::iterator	end = channelMap.end();
	std::map<std::string, Channel>::iterator	channel = channelMap.find(command[1]);
	if (end == channel) {
		numericReply(ERR_NOSUCHCHANNEL, socketClient, userMap, &(command[1]));
		return ;
	}
	if (!channel->second.isInOperSet(socketClient).first) {
		numericReply(ERR_CHANOPRIVSNEEDED, socketClient, userMap, &(command[1]));
		return ;
	}
	std::vector<std::string>	kickList = splitNames(command[2]);
	size_t 						sizeKickList = kickList.size();
	std::vector<User>			onList;
	std::string					notOnList;
	for (size_t i = 0; i < sizeKickList; ++i)
	{
		std::map<int, User>::const_iterator	toKick = findUserByNickName(kickList[i], userMap);
		if (toKick == userMap.end() || !channel->second.isInUserSet(toKick->second.getSocket()).first) {
			if (!notOnList.empty())
				notOnList += ',';
			notOnList += kickList[i];
		}
		else
			onList.push_back(toKick->second);
	}
	if (!notOnList.empty())
		notHereUser(socketClient, userMap, notOnList, command[1]);
	size_t onListSize = onList.size();
	if (onListSize) {
		std::string reason = buildReason(command);
		for (size_t i = 0; i != onListSize; ++i) {
			kickOneByOne(userMap.find(socketClient)->second, onList[i], reason, channel->second);
		}
	}
}
