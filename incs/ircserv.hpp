/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:00:08 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/17 16:38:19 by dvallien         ###   ########.fr       */
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
# include <set>
# include <csignal>
# include <vector>
# include <algorithm>

# include "User.hpp"
# include "Channel.hpp"
# include "numericReply.hpp"

class Channel;

#define SERVER_TALKING ":pouet_irc "
#define SERVER_NAME "pouet_irc"
#define SERVER_DESCRIPTION " Welcome to pouet irc "
#define SERVER_ID "97K"
#define SERVER_NETWORK "pouet.irc.fr"

int							receiveMsg(const int socket, std::string &buffer);
int							assignReadValue(int &a, const int b);
int							sendMsg(const int socket, std::string &str);
int							sendMsg(const int socket, const char * str);
std::string 				delTilde(const std::string &str);
void						delColon(std::string &str);
std::string 				userSource(const User &user);
int							capMsg(const int socket);
int							welcomeMsg(const int socket);
std::vector<std::string>	splitMsg(std::string content);
bool						getInfosClient(int socketClient, std::string content, fd_set *writeSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap);
bool						nickHandle(int socketClient, std::string &nickname, std::map<int, User> &userMap);
bool    					containedNickname(const std::string &name, const std::map<int, User> &userMap);
bool						userHandle(int socketClient, std::vector<std::string> &username, std::map<int, User> &userMap);
void						numericReply(int error, int socketClient, std::map<int, User> &userMap, std::string *context);
int 						checkNickname(const std::string &name);
bool						ping(int socketClient);
bool						pong(int socketClient);
bool						join(int socketClient, std::string &channelNames, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap);
bool						privmsg(int socketClient, std::vector<std::string> msg, fd_set *writeSockets, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap);
bool						part(int socketClient, std::string channels, std::vector<std::string> reason, std::map<int, User> & userMap,std::map<std::string, Channel> &channelMap);
void						kick(int socketClient, std::vector<std::string> &command, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap);
std::vector<std::string> 	splitNames(std::string &names);
bool						names(int socketClient, std::string channelName, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap);
#endif