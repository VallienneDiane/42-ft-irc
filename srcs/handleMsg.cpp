/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/11 14:07:11 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

std::vector<std::string> splitMsg(std::string content)
{
	char *words = new char [content.length()+1]; //to copy string to chat to use strtok
	std::strcpy(words, content.c_str()); 		//copy all client infos in words (cap, nick, user)
	
	char *line = strtok(words, " ");			 //split words into tokens with " "
	std::vector<std::string> clientInfos;		//create tab with client infos
	
	while(line != NULL)
	{
		clientInfos.push_back(line);
		line = strtok(NULL, "\r \n");
	}
	delete[] words;
	return (clientInfos);
}

void	getInfosClient(int socketClient, std::string content, std::map<int, User> &userMap)
{
	std::vector<std::string> clientInfos;
	bool    welcome = false;

	clientInfos = splitMsg(content);
	for(std::vector<std::string>::iterator it = clientInfos.begin(); it != clientInfos.end(); it++)
	{
		if (it->compare("NICK") == 0) {
            if (userMap[socketClient].getNickname().empty())
                welcome = true;
            std::string nickname = *(++it);
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
		}
	}
	
	
	
}
