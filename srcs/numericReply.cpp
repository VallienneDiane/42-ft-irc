/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:55:24 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/21 11:10:21 by dvallien         ###   ########.fr       */
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
			sendMsg(socketClient, str);
			break;
		case 322:
			str += SERVER_TALKING;
			str += "322 ";
			str += *context;
			sendMsg(socketClient, str);
			break;
		case 323:
			str += SERVER_TALKING;
			str += "323 = :End of /LIST";
			sendMsg(socketClient, str);
			break;
		case 341:
			str += SERVER_TALKING;
			str += "341 ";
			str += *context;
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
			str += " 464 ";
			str += " Password incorrect";
			sendMsg(socketClient, str);
			break;
		// JOIN
		case 403:
			str += SERVER_TALKING;
			str += " 403 ";
			str += *context;
			str += " :No such channel";
			sendMsg(socketClient, str);
			break;
		case 404:
			str += SERVER_TALKING;
			str += " 404 ";
			str += *context;
			str += " :Cannot send to channel";
			sendMsg(socketClient, str);
			break;
		case 475:
			str += SERVER_TALKING;
			str += " 475 ";
			str += *context;
			str += " :Cannot join the channel";
			sendMsg(socketClient, str);
			break;
		//TOPIC
		case 332:
			str += SERVER_TALKING;
			str += "332 ";
			str += *context;
			sendMsg(socketClient, str);
			break;
		case 333:
			str = SERVER_TALKING;
			str += "333 ";
			str += *context;
			sendMsg(socketClient, str);
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
			str = SERVER_TALKING;
			str += " 401 ";
			str += *context;
			str += " :No such nick";
			sendMsg(socketClient, str);
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