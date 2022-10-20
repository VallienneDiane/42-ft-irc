/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:55:24 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/20 15:33:17 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

void	numericReply(int error, int socketClient, std::map<int, User> &userMap, std::string *context)
{
	std::string str;
	std::string msg;
	User & user = userMap[socketClient];
	switch(error)
	{
		case 001:
			str += SERVER_TALKING;
			str += "001 ";
			str += user.getNickname();
			str += " :Welcome to the ";
			str += SERVER_NAME;
			str += " Network, ";
			str += userSource(user);
			std::cout << "welcome msg : " << str << std::endl;
			sendMsg(socketClient, str);
			break;
		// NICKNAME
		case 431:
			str += SERVER_TALKING;
			str += " 431 :Nickname is empty.";
			sendMsg(socketClient, str);
			break;
		case 432:
			str += SERVER_TALKING;
			str += " 432 ";
			str += *context;
			if (context->size() > 20)
				str += " :Nickname is too long (it will pollute the chat).";
			else if (!isalpha((*context)[0]))
				str += " :Nickname has to begin with a letter.";
			else
				str += " :Nickname must only contain alphanum characters or underscores.";
			sendMsg(socketClient, str);
			break;
		case 433:
			str += SERVER_TALKING;
			str += " 433 ";
			str += *context;
			str += " :this nickname is already in use, try another nickname.";
			sendMsg(socketClient, str);
			break;
		case 436:
			std::cout << "<client> " << userMap[socketClient].getNickname() << " <channel> :They aren't on that channel" << std::endl;
			break;
		//PART
		case 442:
			str += SERVER_TALKING;
			str += " 442 ";
			str += *context;
			str += " :You're not on that channel";
			sendMsg(socketClient, str);
			break;
		// USERNAME
		case 461:
			str += SERVER_TALKING;
			str += " 461 ";
			str += *context;
			str += " Not enough parameters";
			sendMsg(socketClient, str);
			break;
		case 462:
			str += SERVER_TALKING;
			str += "462 :You may not reregister";
			sendMsg(socketClient, str);
			break;
		// OPER
		case 464:
			str += SERVER_TALKING;
			str += "464 :Incorrect password";
			sendMsg(socketClient, str);
			break;
		case 491:
			std::cout << "<client> :No O-lines for your host" << std::endl;
			break;
		// JOIN
		case 403:
			str += SERVER_TALKING;
			str += " 403 ";
			str += *context;
			str += " :No such channel";
			sendMsg(socketClient, str);
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
		case 331:
			str += SERVER_TALKING;
			str += " 331 ";
			str += *context;
			str += " :";
			str += *context;
			sendMsg(socketClient, str);
			break;
		case 332:
			str += SERVER_TALKING;
			str += " 332 ";
			str += *context;
			sendMsg(socketClient, str);
			break;
		case 333:
			str = SERVER_TALKING;
			str += "333 ";
			str += *context;
			sendMsg(socketClient, str);
		//INVITE
		case 443:
			std::cout << "<client> <nick> <channel> :is already on channel" << std::endl;
			break;
		//KICK
		case 441:
			str += SERVER_TALKING;
			str += "441 ";
			str += *context;
			str += " :They aren't on that channel";
			sendMsg(socketClient, str);
			break;
		case 476:
			std::cout << "<channel> :Bad Channel Mask" << std::endl;
			break;
		case 482:
			str += SERVER_TALKING;
			str += "482 ";
			str += *context;
			str += " :You're not channel operator";
			sendMsg(socketClient, str);
			break;
		//PRIVMSG
		case 401:
			// std::cout << "<client> <nickname> :No such nick/channel" << std::endl;
			str = SERVER_TALKING;
			str += " 401 ";
			str += *context;
			str += " :No such nick";
			sendMsg(socketClient, str);
			break;
		case 404:
			std::cout << "<client> <channel> :Cannot send to channel" << std::endl;
			break;
		//OTHER ERRORS
		case 451:
			str += SERVER_TALKING;
			str += "451 ";
			str += ":";
			str += *context;
			sendMsg(socketClient, str);
			break;
	}
}