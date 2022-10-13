/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loginMsg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/12 15:01:13 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

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
        sendMsg(socketClient, "Sorry :( this nickname is already used.\r\n");
    else
	{
		std::cout << BCYAN << "setNickname" << END << std::endl;
        userMap[socketClient].setNickname(nickname);
	}
	return (0);
}

void	userHandle(int socketClient, std::string username, std::map<int, User> &userMap)
{
	(void)socketClient;
	(void)username;
	(void)userMap;
	// bool    welcome = false;
	
	// if (userMap[socketClient].getUsername().empty())
	// 			welcome = true;
	// userMap[socketClient].setUsername(username);
	// if (welcome)
	// {
	// 	std::string welcomeStr = SERVER_TALKING;
	// 	welcomeStr += "001 ";
	// 	welcomeStr += userMap[socketClient].getUsername();
	// 	welcomeStr += "userhandle";
	// 	welcomeStr += SERVER_DESCRIPTION;
	// 	welcomeStr += userMap[socketClient].getUsername();
	// 	welcomeStr += " !";
	// 	sendMsg(socketClient, welcomeStr);
	// }
}