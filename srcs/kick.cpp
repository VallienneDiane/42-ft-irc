#include "../incs/ircserv.hpp"

void	kick(int socketClient, std::vector<std::string> &command, std::map<int, User> &userMap, std::map<std::string, Channel> &channelMap)
{
	std::map<std::string, Channel>::iterator	end = channelMap.end();
	std::map<std::string, Channel>::iterator	channel = channelMap.find(command[1]);
	if (end == channel)
	{
		numericReply(ERR_NOSUCHCHANNEL, socketClient, userMap, &(command[1]));
		return ;
	}
	//if (channel->second.getOperList())
	std::vector<std::string>	kickList = splitNames(command[2]);
}