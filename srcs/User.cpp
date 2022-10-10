/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:45:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/10 10:17:53 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

/****************** CANONIC FORM ******************/
User::User(void) : _nickname("nickname"), _username("username"), _id(0)
{}

User::User(const User &src)
{
	*this = src;
}

User & User::operator=(const User &src)
{
	this->_nickname = src.getNickname();
	this->_username = src.getUsername();
	this->_id = src.getId();
	return (*this);
}

User::~User(void)
{}

/****************** CONSTRUCTOR BY NAME ******************/
User::User(std::string nickname, std::string username, unsigned int id)
{
	this->_nickname = nickname;
	this->_username = username;
	this->_id = id;
}

/****************** SETTERS ******************/
void	User::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void	User::setUsername(std::string username)
{
	this->_username = username;
}

void	User::setId(unsigned int id)
{
	this->_id = id;
}

/****************** GETTERS ******************/
std::string User::getNickname(void) const
{
	return (this->_nickname);
}

std::string User::getUsername(void) const
{
	return (this->_username);
}

unsigned int User::getId(void) const
{
	return (this->_id);
}