/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/11 16:02:07 by dvallien         ###   ########.fr       */
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


	clientInfos = splitMsg(content);
	for(std::vector<std::string>::iterator it = clientInfos.begin(); it != clientInfos.end(); it++)
	{
		if (it->compare("NICK") == 0) 
			nickHandle(socketClient, *(++it), &userMap);
	}
}

