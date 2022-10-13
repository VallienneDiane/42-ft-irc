/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:00:08 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 12:59:02 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define BRED "\x1B[91m"
# define BGREEN "\x1B[92m"
# define BYELLOW "\x1B[93m"
# define BBLUE "\x1B[94m"
# define BMAGENTA "\x1B[95m"
# define BCYAN "\x1B[96m"
# define WHITE "\x1B[97m"
# define END "\033[0m"

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
# include "numericReply.hpp"

#define SERVER_TALKING ":pouet_irc "
#define SERVER_NAME "pouet_irc"
#define SERVER_DESCRIPTION " Welcome to pouet irc "
#define SERVER_ID "97K"
#define SERVER_NETWORK "pouet.irc.fr"

int							receiveMsg(const int socket, std::string &buffer);
int							sendMsg(const int socket, std::string &str);
int							sendMsg(const int socket, const char * str);
int							capMsg(const int socket);
int							welcomeMsg(const int socket);
std::vector<std::string>	splitMsg(std::string content);
bool						getInfosClient(int socketClient, std::string content, std::map<int, User> &userMap);
bool						nickHandle(int socketClient, const std::string &nickname, std::map<int, User> &userMap);
bool    					containedNickname(const std::string name, const std::map<int, User> &userMap);
bool						userHandle(int socketClient, const std::string &username, const std::string &realname, std::map<int, User> &userMap);
void						numericReply(int error, int socketClient, std::map<int, User> &userMap);
void						checkNichname(const std::string name);
bool						ping(int socketClient);
bool						pong(int socketClient);

#endif