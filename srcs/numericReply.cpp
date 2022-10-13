/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:55:24 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 10:30:07 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

void	numericReply(int error)
{
	switch(error)
	{
		// NICKNAME
		case 431:
			break;
		case 432:
			std::cout <<  "<client> <nick> :Erroneus nickname" << std::endl;
			break;
		case 433:
			std::cout <<  "<client> <nick> :Nickname is already in use" << std::endl;
			break;
		case 436:
			std::cout <<  "<client> <nick> <channel> :They aren't on that channel" << std::endl;
			break;
		// USERNAME
		case 461:
			std::cout << "<client> <command> :Not enough parameters" << std::endl;
			break;
		case 462:
			std::cout << "<client> :You may not reregister" << std::endl;
			break;
		// PING
		case 409:
			std::cout << "<client> :No origin specified" << std::endl;
			break;
		case 402:
			std::cout << "<client> <server name> :No such server" << std::endl;
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
		
	}
}