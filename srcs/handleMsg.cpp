/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/11 16:25:53 by dvallien         ###   ########.fr       */
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

bool	getInfosClient(int socketClient, std::string content, std::map<int, User> &userMap)
{
	std::vector<std::string> clientInfos;

	clientInfos = splitMsg(content);
	std::vector<std::string>::iterator itEnd = clientInfos.end();
	for(std::vector<std::string>::iterator it = clientInfos.begin(); it != itEnd; it++)
	{
		if (it->compare("NICK") == 0)
		{
			std::cout << "nick " << std::endl;
			return (nickHandle(socketClient, *(++it), userMap));
		}
		if (it->compare("USER") == 0)
		{
			std::string username = *(++it);
			std::cout << "user " << std::endl;
		}
	}
    return false;
}

