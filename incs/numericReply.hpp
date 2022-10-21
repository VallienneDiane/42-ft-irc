/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReply.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:04:35 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/21 11:06:53 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREPLY_HPP
# define NUMERICREPLY_HPP

#define RPL_WELCOME 001
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
#define ERR_CHANNELISFULL 471
#define ERR_INVITEONLYCHAN 473
#define ERR_BANNEDFROMCHAN 474
#define ERR_BADCHANNELKEY 475
// PART
#define ERR_NOTONCHANNEL 442
// TOPIC
#define RPL_NOTOPIC 331
#define RPL_TOPIC 332
#define RPL_TOPICWHOTIME 333
// INVITE
// #define ERR_USERONCHANNEL 443
// KICK
#define ERR_USERNOTINCHANNEL 441
#define ERR_BADCHANMASK 476
#define ERR_CHANOPRIVSNEEDED 482
//PRIVMSG
#define ERR_NOSUCHNICK 401
#define ERR_CANNOTSENDTOCHAN 404

#define ERR_YOUREBANNEDCREEP 465
#define ERR_UNKNOWNMODE 472
#define ERR_NOPRIVILEGES 481
#define ERR_CANTKILLSERVER 483
#define ERR_UMODEUNKNOWNFLAG 501
#define ERR_USERSDONTMATCH 502
#define ERR_HELPNOTFOUND 524
#define ERR_INVALIDKEY 525
#define RPL_STARTTLS 670
#define RPL_WHOISSECURE 671
#define ERR_STARTTLS 691
#define ERR_INVALIDMODEPARAM 696
#define RPL_HELPSTART 704
#define RPL_HELPTXT 705
#define RPL_ENDOFHELP 706
#define ERR_NOPRIVS 723
#define RPL_LOGGEDIN 900
#define RPL_LOGGEDOUT 901
#define ERR_NICKLOCKED 902
#define RPL_SASLSUCCESS 903
#define ERR_SASLFAIL 904
#define ERR_SASLTOOLONG 905
#define ERR_SASLABORTED 906
#define ERR_SASLALREADY 907
#define RPL_SASLMECHS 908
#define ERR_NOTREGISTERED 451

#endif