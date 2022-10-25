/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingPong.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:42:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/14 16:48:15 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

bool	ping(int socketClient)
{
	return (sendMsg(socketClient, "PONG\r\n") == -1);
}

bool	pong(int socketClient, std::string &ping)
{
	ping[1] = 'O';
	ping.insert(5, "pouet_irc ");
	ping.insert(0, SERVER_TALKING);
	return (sendMsg(socketClient, ping) == -1);
}
