/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:42:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/20 16:51:56 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

bool	notice(int socketClient, std::vector<std::string> msg, fd_set *writeSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	 
}