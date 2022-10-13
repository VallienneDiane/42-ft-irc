/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:55:24 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 14:00:07 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

void	numericReply(int error, int socketClient, std::map<int, User> &userMap)
{
	std::string str;
	User & user = userMap[socketClient];
	switch(error)
	{
		case 001:
			str = "001 ";
			str += user.getNickname();
			str += " :Welcome to the ";
			str += SERVER_NAME;
			str += " Network, ";
			str += user.getNickname();
			str += "!" ;
			str += user.getUsername();
			str += "@";
			str += user.getHostname();
			sendMsg(socketClient, str);
			break;
		// NICKNAME
		case 431:
			break;
		case 432:
			std::cout << "<client> " << userMap[socketClient].getNickname() << ":Erroneus nickname" << std::endl;
			break;
		case 433:
			std::cout << "<client> " << userMap[socketClient].getNickname() << ":Nickname is already in use" << std::endl;
			break;
		case 436:
			std::cout << "<client> " << userMap[socketClient].getNickname() << " <channel> :They aren't on that channel" << std::endl;
			break;
		//PART
		case 442:
			std::cout << "<client> <channel> :You're not on that channel" << std::endl;
			break;
		// USERNAME
		case 461:
			std::cout << "<client> <command> :Not enough parameters" << std::endl;
			break;
		case 462:
			std::cout << "<client> :You may not reregister" << std::endl;
			break;
		// OPER
		case 464:
			std::cout << "<client> :Password incorrect" << std::endl;
			break;
		case 491:
			std::cout << "<client> :No O-lines for your host" << std::endl;
			break;
		// JOIN
		case 403:
			std::cout << "<client> <channel> :No such channel" << std::endl;
			break;
		case 471:
			std::cout << "<client> <channel> :Cannot join channel (+l)" << std::endl;
			break;
		case 473:
			std::cout << "<client> <channel> :Cannot join channel (+i)" << std::endl;
			break;
		case 474:
			std::cout << "<client> <channel> :Cannot join channel (+b)" << std::endl;
			break;
		case 475:
			std::cout << "<client> <channel> :Cannot join channel (+k)" << std::endl;
			break;
		//TOPIC
		case 482:
			std::cout << "<client> <channel> :You're not channel operator" << std::endl;
			break;
		//INVITE
		case 443:
			std::cout << "<client> <nick> <channel> :is already on channel" << std::endl;
			break;
		//KICK
		case 441:
			std::cout << "<client> <nick> <channel> :They aren't on that channel" << std::endl;
			break;
		case 476:
			std::cout << "<channel> :Bad Channel Mask" << std::endl;
			break;
		//PRIVMSG
		case 401:
			std::cout << "<client> <nickname> :No such nick/channel" << std::endl;
			break;
		case 404:
			std::cout << "<client> <channel> :Cannot send to channel" << std::endl;
			break;
	}
}