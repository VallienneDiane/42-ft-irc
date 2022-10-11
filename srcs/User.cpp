/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:45:49 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/11 11:10:52 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/User.hpp"

/****************** CANONIC FORM ******************/
User::User(void) : _socket(0), _nickname(""), _username(""), _id(0)
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
void	User::setSocket(int socket)
{
	this->_socket = socket;
}

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
int User::getSocket(void) const
{
	return (this->_socket);
}

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

/****************** STREAM OVERLOAD ******************/
std::ostream &operator<<(std::ostream &stream, const User &source)
{
	stream 	<< "~~ User ~~" << std::endl
			<< "Socket\t:" << source.getSocket() << std::endl
			<< "Nickname\t:" << source.getNickname() << std::endl
			<< "Username\t:" << source.getUsername() << std::endl;
	return (stream);
}