#include "../incs/ircserv.hpp"

void	doTheInvite(User &user, User &invited, Channel &chan, std::map<int, User> &userMap) {
	std::string	message = userSource(user) + " INVITE " + invited.getNickname() + " " + chan.getName();
	std::string	reply = user.getNickname() + " " + invited.getNickname() + " " + chan.getName();
	chan.addUser(invited);
	invited.addChannel(chan.getName());
	numericReply(RPL_INVITING, user.getSocket(), userMap, &reply);
	chan.sendToUsers(message, user.getSocket());
	message.assign(":" + invited.getNickname() + " JOIN " + chan.getName());
	chan.sendToUsers(message, 0);
}

void    invite(User &user, std::vector<std::string> &command, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap) {
    if (command.size() < 3) {
        numericReply(ERR_NEEDMOREPARAMS, user.getSocket(), userMap, NULL);
		return ;
    }
	std::map<int, User>::iterator	userIt = findUserByNickName(command[1], userMap);
	if (userIt == userMap.end()) {
		numericReply(ERR_NOSUCHNICK, user.getSocket(), userMap, &(command[1]));
		return ;
	}
	std::map<std::string, Channel>::iterator	chanIt = channelMap.find(command[2]);
	if (chanIt == channelMap.end()) {
		numericReply(ERR_NOSUCHCHANNEL, user.getSocket(), userMap, &(command[2]));
		return ;
	}
	if (!chanIt->second.isInUserSet(user.getSocket()).first) {
		numericReply(ERR_NOTONCHANNEL, user.getSocket(), userMap, &(command[2]));
		return ;
	}
	if (chanIt->second.isInUserSet(userIt->first).first) {
		std::string	context = command[1] + " " + command[2];
		numericReply(ERR_USERONCHANNEL, user.getSocket(), userMap, &context);
		return ;
	}
	doTheInvite(user, userIt->second, chanIt->second, userMap);
}