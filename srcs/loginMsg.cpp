/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loginMsg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 13:09:37 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ircserv.hpp"

void	checkNichname(const std::string name)
{
    (void)name;
}

bool    containedNickname(const std::string name, const std::map<int, User> &userMap)
{
    std::map<int, User>::const_iterator end = userMap.end();
    for (std::map<int, User>::const_iterator it = userMap.begin(); it != end; ++it)
    {
        if (!it->second.getNickname().compare(name))
            return true;
    }
    return false;
}

bool    nickHandle(int socketClient, const std::string &nickname, std::map<int, User> &userMap)
{
	bool    welcome = false;
	User    &current = userMap[socketClient];
	if (current.getNickname().empty())
				welcome = true;
	std::string nickAnswer;
	if (welcome)
	{
        if (!containedNickname(nickname, userMap))
        {
<<<<<<< HEAD
			nickAnswer += SERVER_TALKING;
            current.setNickname(nickname);
            nickAnswer += " 001 ";
	        nickAnswer += current.getNickname();
	        nickAnswer += SERVER_DESCRIPTION;
	        nickAnswer += current.getNickname();
	        nickAnswer += " !";
=======
            userMap[socketClient].setNickname(nickname);
            std::string welcomeStr = SERVER_TALKING;
            // numericReply(RPL_WELCOME, socketClient, userMap);
            welcomeStr += "001 ";
            welcomeStr += userMap[socketClient].getNickname();
            welcomeStr += SERVER_DESCRIPTION;
            welcomeStr += userMap[socketClient].getNickname();
            welcomeStr += " !";
            sendMsg(socketClient, welcomeStr);
>>>>>>> 4b99febd676fb2c4bf144b5a451f4de7054418a8
        }
        else
        {
	        nickAnswer += SERVER_TALKING;
			nickAnswer += " ";
			nickAnswer += ERR_NICKNAMEINUSE;
			nickAnswer += " ";
			nickAnswer += nickname;
			nickAnswer += " :this nickname is already in use, please use another one.";
            sendMsg(socketClient, nickAnswer);
            userMap.erase(socketClient);
            close(socketClient);
            return (1);
        }
	}
    else if (containedNickname(nickname, userMap))
<<<<<<< HEAD
	{
		nickAnswer += SERVER_TALKING;
		nickAnswer += " ";
		nickAnswer += ERR_NICKNAMEINUSE;
		nickAnswer += " ";
		nickAnswer += nickname;
		nickAnswer += " :this nickname is already in use, please use another one.";
	}
	else
	{
		nickAnswer += ":";
		nickAnswer += current.getNickname();
		nickAnswer += "!njaros@127.0.0.1 ";
		current.setNickname(nickname);
		nickAnswer += " NICK ";
		nickAnswer += nickname;
	}
	sendMsg(socketClient, nickAnswer);
=======
        sendMsg(socketClient, "Sorry, this nickname is already used.\r\n");
    else
	{
		std::cout << BCYAN << "setNickname" << END << std::endl;
        userMap[socketClient].setNickname(nickname);
	}
>>>>>>> 4b99febd676fb2c4bf144b5a451f4de7054418a8
	return (0);
}

bool	userHandle(int socketClient, const std::string &username, const std::string &realname, std::map<int, User> &userMap)
{
	bool    welcome = false;
	
	if (userMap[socketClient].getUsername().empty() && userMap[socketClient].getRealname().empty())
		welcome = true;
	else
	{
<<<<<<< HEAD
		//numericReply(ERR_ALREADYREGISTERED);
=======
		numericReply(ERR_ALREADYREGISTERED, socketClient, userMap);
>>>>>>> 4b99febd676fb2c4bf144b5a451f4de7054418a8
		return (1);
	}
	userMap[socketClient].setUsername(username);
	userMap[socketClient].setRealname(realname);
	return (0);
}


void    operMsg()