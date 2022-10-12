/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:00:08 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/12 11:00:43 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
# include <map>
# include <csignal>
# include <vector>

# include "User.hpp"
# include "Channel.hpp"

#define SERVER_TALKING ":pouet_irc "
#define SERVER_NAME "pouet_irc"
#define SERVER_DESCRIPTION " Welcome to pouet irc "
#define SERVER_ID "97K"
#define SERVER_NETWORK "pouet.irc.fr"

int                         receiveMsg(const int socket, std::string &buffer);
int                         sendMsg(const int socket, std::string &str);
int                         sendMsg(const int socket, const char * str);
int                         capMsg(const int socket);
int                         welcomeMsg(const int socket);
std::vector<std::string>	splitMsg(std::string content);
void	getInfosClient(int socketClient, std::string content, std::map<int, User> &userMap);

#endif