/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReply.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:04:35 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/21 11:50:09 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREPLY_HPP
# define NUMERICREPLY_HPP

#define RPL_WELCOME 001
// LIST
#define RPL_LIST 322
#define RPL_LISTEND 323
#define RPL_INVITING 341
// NICKNAME
#define ERR_NONICKNAMEGIVEN 431
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NICKCOLLISION 436
// USERNAME
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTERED 462
// OPER
#define ERR_PASSWDMISMATCH 464
#define ERR_NOOPERHOST 491
// JOIN
#define ERR_NOSUCHCHANNEL 403
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_CHANNELISFULL 471
#define ERR_INVITEONLYCHAN 473
#define ERR_BANNEDFROMCHAN 474
#define ERR_BADCHANNELKEY 475
#define ERR_USERONCHANNEL 443
// PART
#define ERR_NOTONCHANNEL 442
// TOPIC
#define RPL_TOPIC 332
#define RPL_TOPICWHOTIME 333
// KICK
#define ERR_USERNOTINCHANNEL 441
#define ERR_BADCHANMASK 476
#define ERR_CHANOPRIVSNEEDED 482
//PRIVMSG
#define ERR_NOSUCHNICK 401
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_NOTREGISTERED 451
//MODE
#define ERR_UMODEUNKNOWNFLAG 501

#endif