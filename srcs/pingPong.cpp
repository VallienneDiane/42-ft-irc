/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pingPong.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:42:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/10/13 14:44:26 by dvallien         ###   ########.fr       */
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
