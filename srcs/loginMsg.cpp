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

bool nickHandle(int socketClient, std::string nickname, std::map<int, User> &userMap)
{
	bool    welcome = false;
	
	if (userMap[socketClient].getNickname().empty())
				welcome = true;
	userMap[socketClient].setNickname(nickname);
	if (welcome)
	{
		std::string welcomeStr = SERVER_TALKING;
		welcomeStr += "001 ";
		welcomeStr += userMap[socketClient].getNickname();
		welcomeStr += "_le_boss";
		welcomeStr += SERVER_DESCRIPTION;
		welcomeStr += userMap[socketClient].getNickname();
		welcomeStr += " !";
		sendMsg(socketClient, welcomeStr);
	}
	return (0);
}