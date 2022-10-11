/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:17 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/11 11:51:38 by dvallien         ###   ########.fr       */
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
		std::cout << "Line : " << line << std::endl;
		clientInfos.push_back(line);
		// std::cout << "Line2 : " << clientInfos.back() << std::endl;
		line = strtok(NULL, "\r \n");
	}
	delete[] words;
	return (clientInfos);
}

void	getInfosClient(int socketClient, std::string content) //, std::map<int, User> repertory
{
	(void)socketClient;
	std::cout << content << std::endl;
	splitMsg(content);
}
