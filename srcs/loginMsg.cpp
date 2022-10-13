/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loginMsg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:25 by dvallien          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/11 16:05:06 by dvallien         ###   ########.fr       */
=======
/*   Updated: 2022/10/13 10:31:07 by dvallien         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

<<<<<<< HEAD
=======
void	checkNichname(const std::string name)
{
    (void)name;
}

>>>>>>> master
bool    containedNickname(const std::string name, const std::map<int, User> &userMap)
{
    std::map<int, User>::const_iterator end = userMap.end();
    for (std::map<int, User>::const_iterator it = userMap.begin(); it != end; ++it)
    {
        if (!it->second.getNickname().compare(name))
            return true;
    }
    return false;
}

bool    nickHandle(int socketClient, const std::string &nickname, std::map<int, User> &userMap)
{
	bool    welcome = false;
	
	if (userMap[socketClient].getNickname().empty())
				welcome = true;
	if (welcome)
	{
        if (!containedNickname(nickname, userMap))
        {
            userMap[socketClient].setNickname(nickname);
            std::string welcomeStr = SERVER_TALKING;
            welcomeStr += "001 ";
            welcomeStr += userMap[socketClient].getNickname();
            welcomeStr += "_le_capouet";
            welcomeStr += SERVER_DESCRIPTION;
            welcomeStr += userMap[socketClient].getNickname();
            welcomeStr += " !";
            sendMsg(socketClient, welcomeStr);
        }
        else
        {
            sendMsg(socketClient, "Sorry, this nickname is already used : connection refused :(\r\n");
            userMap.erase(socketClient);
            close(socketClient);
            return (1);
        }
	}
    else if (containedNickname(nickname, userMap))
        sendMsg(socketClient, "Sorry, this nickname is already used.\r\n");
    else
        userMap[socketClient].setNickname(nickname);
	return (0);
}

bool	userHandle(int socketClient, const std::string &username, const std::string &realname, std::map<int, User> &userMap)
{
	bool    welcome = false;
	
	if (userMap[socketClient].getUsername().empty() && userMap[socketClient].getRealname().empty())
		welcome = true;
	else
	{
		numericReply(ERR_ALREADYREGISTERED);
		return (1);
	}
	userMap[socketClient].setUsername(username);
	userMap[socketClient].setRealname(realname);
	return (0);
}

