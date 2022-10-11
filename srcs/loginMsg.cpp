/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loginMsg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/11 16:05:06 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool    containedNickname(std::string name, std::map<int, User> &userMap)
{
    std::map<int, User>::iterator end = userMap.end();
    for (std::map<int, User>::iterator it = userMap.begin(); it != end; ++it)
    {

    }
}

bool    nickHandle(int socketClient, std::string nickname, std::map<int, User> &userMap)
{
	bool    welcome = false;
	
	if (userMap[socketClient].getNickname().empty())
				welcome = true;
	if (welcome)
	{
        if (!containedNickname(nickname, userMap))
        {
            std::string welcomeStr = SERVER_TALKING;
            welcomeStr += "001 ";
            welcomeStr += userMap[socketClient].getNickname();
            welcomeStr += "_le_boss";
            welcomeStr += SERVER_DESCRIPTION;
            welcomeStr += userMap[socketClient].getNickname();
            welcomeStr += " !";
            sendMsg(socketClient, welcomeStr);
            userMap[socketClient].setNickname(nickname);
        }
        else
        {
            userMap.erase(socketClient);
            close(socketClient);
            return (1);
        }
	}
    else
        userMap[socketClient].setNickname(nickname);
	return (0);
}