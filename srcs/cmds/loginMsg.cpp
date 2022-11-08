/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loginMsg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:25:39 by njaros            #+#    #+#             */
/*   Updated: 2022/11/07 13:25:39 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

bool	isNotAlNumOrUnderscore(char c)
{
	return (!(isalnum(c) || c == '_'));
}

int	checkNickname(const std::string &name)
{
	if (name.empty())
		return (1);
	if (name.size() > 20 || !isalpha(name[0]) ||
			std::find_if(name.begin(), name.end(), isNotAlNumOrUnderscore) != name.end())
		return (2);
	return (0);
}

bool    containedNickname(const std::string &name, const std::map<int, User> &userMap)
{
    std::map<int, User>::const_iterator end = userMap.end();
    for (std::map<int, User>::const_iterator it = userMap.begin(); it != end; ++it)
    {
        if (!it->second.getNickname().compare(name))
            return true;
    }
    return false;
}

void	nickReplyError(int err, int socketClient, std::map<int, User> &userMap, std::string *context)
{
	switch (err)
	{
		case 1:
			numericReply(ERR_NONICKNAMEGIVEN, socketClient, userMap, context);
			break;
		case 2:
			numericReply(ERR_ERRONEUSNICKNAME, socketClient, userMap, context);
			break;
		default:
			numericReply(ERR_NICKNAMEINUSE, socketClient, userMap, context);
	}
}

void	changeNickname(User &user, std::string &nickname, std::map<std::string, Channel> &channelMap, std::map<int, User> &userMap)
{
	std::set<int>::iterator			itPrivateEnd = user.getPrivMsg().end();
	std::string	nickAnswer;
	nickAnswer += userSource(user);
	user.setNickname(nickname);
	nickAnswer += " NICK ";
	nickAnswer += nickname;
	user.addMsgToBuffer(nickAnswer);
	std::set<std::string>::iterator	itChanEnd = user.getChannels().end();
	for (std::set<std::string>::iterator it = user.getChannels().begin(); it != itChanEnd; it++) {
		std::map<std::string, Channel>::iterator	found = channelMap.find(*it);
		if (found != channelMap.end())
			found->second.sendToUsers(nickAnswer, user.getSocket(), userMap);
	}
	for (std::set<int>::iterator it = user.getPrivMsg().begin(); it != itPrivateEnd; ++it) {
		userMap[*it].addMsgToBuffer(nickAnswer);
	}
}

bool    nickHandle(int socketClient, std::string &nickname, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	bool		welcome = false;
	int 		checkNick;
	User		&current = userMap[socketClient];

	if (current.getNickname().empty())
				welcome = true;
	if (welcome)
	{
        if (!assignReadValue(checkNick, checkNickname(nickname)) && !containedNickname(nickname, userMap))
        {
            current.setNickname(nickname);
			if (fullyRegistered(current))
            	numericReply(RPL_WELCOME, socketClient, userMap, NULL);
        }
        else
        {
			nickReplyError(checkNick, socketClient, userMap, &nickname);
			//userMap.erase(socketClient);
			//close(socketClient);
            return (0);
        }
	}
    else if (assignReadValue(checkNick, checkNickname(nickname)) || containedNickname(nickname, userMap))
		nickReplyError(checkNick, socketClient, userMap, &nickname);
	else
		changeNickname(current, nickname, channelMap, userMap);
	return (0);
}

bool	identServer(std::string &ident)
{
	/////// If we want to auto-generate username for some ident, we do it here
	if (ident.empty()) {
		ident.assign("unknown");
		return true;
	}
	if (ident.length() > 12) {
		std::string::iterator start = ident.begin();
		start += 11;
		ident.erase(start, ident.end());
	}
		return false;
}

bool	userHandle(int socketClient, std::vector<std::string> &username, std::map<int, User> &userMap)
{
	User	&current = userMap[socketClient];

	if (!current.getUsername().empty())
	{
		numericReply(ERR_ALREADYREGISTERED, socketClient, userMap, NULL);
		return (0);
	}
	if (username.size() < 5)
	{
		numericReply(ERR_NEEDMOREPARAMS, socketClient, userMap, &username[0]);
		//userMap.erase(socketClient);
		return (0);
	}
	if (!identServer(username[1]))
		username[1].insert(username[1].begin(), '~');
	current.setUsername(username[1]);
	delColon(username[4]);
	if (username[4].empty())
		username[4].assign("Gordon Freeman");
	current.setRealname(username[4]);
	if (fullyRegistered(current))
	numericReply(RPL_WELCOME, socketClient, userMap, NULL);
	return (0);
}
