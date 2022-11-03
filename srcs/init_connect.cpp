/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_connect.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:13:46 by dvallien          #+#    #+#             */
/*   Updated: 2022/11/03 10:13:46 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

int capMsg(const int socket)
{
    std::string str = SERVER_TALKING;
    str += "CAP * LS :";
    return sendMsg(socket, str);
}

int welcomeMsg(const int socket)
{
    std::string str = SERVER_TALKING;
    str += "001 njaros ";
    str += SERVER_DESCRIPTION;
    str += " njaros!";
    return sendMsg(socket, str);
}