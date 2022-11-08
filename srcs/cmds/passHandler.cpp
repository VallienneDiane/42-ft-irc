/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:25:54 by njaros            #+#    #+#             */
/*   Updated: 2022/11/07 13:25:54 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ircserv.hpp"

std::string	getSetPassUser(std::string passSet) {
	static std::string	pass;
	if (!passSet.empty())
		pass = passSet;
	return pass;
}

std::string	getPass() {
	std::string empty;
	return (getSetPassUser(empty));
}

void	setPass(std::string pass) {
	getSetPassUser(pass);
}

bool	passHandle(User &user, std::vector<std::string> &content, std::map<int, User> &userMap) {
	if (user.getPass())
	{
		numericReply(ERR_ALREADYREGISTERED, user.getSocket(), userMap, NULL);
		return false;
	}
	if (content.size() < 2) {
		numericReply(ERR_NEEDMOREPARAMS, user.getSocket(), userMap, &(content[0]));
		return false;
	}
	if (getPass().compare(content[1])) {
		numericReply(ERR_PASSWDMISMATCH, user.getSocket(), userMap, NULL);
		return false;
	}
	user.setPassOk();
	return false;
}