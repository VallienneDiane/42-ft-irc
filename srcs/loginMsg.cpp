/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loginMsg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 16:02:04 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	isNotAlNumOrUnderscore(char c)
{
	return (!(isalnum(c) || c == '_'));
}

int	checkNickname(const std::string &name)
{
	if (name.empty())
		return (1);
	if (name.size() > 20 || !isalpha(name.front()) ||
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

bool    nickHandle(int socketClient, std::string &nickname, std::map<int, User> &userMap)
{
	bool		welcome = false;
	std::string	nickAnswer;
	int 		checkNick;
	User		&current = userMap[socketClient];

	if (current.getNickname().empty())
				welcome = true;
	if (welcome)
	{
        if (!assignReadValue(checkNick, checkNickname(nickname)) && !containedNickname(nickname, userMap))
        {
            current.setNickname(nickname);
            numericReply(RPL_WELCOME, socketClient, userMap, nullptr);
        }
        else
        {
			nickReplyError(checkNick, socketClient, userMap, &nickname);
			userMap.erase(socketClient);
			close(socketClient);
            return (1);
        }
	}
    else if (assignReadValue(checkNick, checkNickname(nickname)) || containedNickname(nickname, userMap))
		nickReplyError(checkNick, socketClient, userMap, &nickname);
	else
	{
		nickAnswer += userSource(current);
		current.setNickname(nickname);
		nickAnswer += " NICK ";
		nickAnswer += nickname;
		sendMsg(socketClient, nickAnswer);
	}
	return (0);
}

bool	userHandle(int socketClient, const std::string &username, const std::string &realname, std::map<int, User> &userMap)
{
	bool    welcome = false;
	
	if (userMap[socketClient].getUsername().empty() && userMap[socketClient].getRealname().empty())
		welcome = true;
	else
	{
		numericReply(ERR_ALREADYREGISTERED, socketClient, userMap, nullptr);
		return (1);
	}
	userMap[socketClient].setUsername(username);
	userMap[socketClient].setRealname(realname);
	return (0);
}
