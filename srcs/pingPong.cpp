/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingPong.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:42:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/12 15:17:01 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	ping(int socketClient)
{
	return (sendMsg(socketClient, "PONG\r\n"));
}

bool	pong(int socketClient)
{
	return (sendMsg(socketClient, "PING 127.0.0.1\r\n"));
}