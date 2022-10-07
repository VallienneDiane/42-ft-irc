/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:00:08 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/07 11:32:05 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP
# include <iostream>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <unistd.h>
# include <cerrno>
# include <map>
# include <string>

int receiveMsg(const int socket, std::string &buffer);
int sendMsg(const int socket, std::string &str);
int sendMsg(const int socket, const char * str);

#endif