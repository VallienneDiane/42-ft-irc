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
User::User(void) : _socket(0), _id(0)
{}

User::User(const User &src) : _socket(src._socket), _nickname(src._nickname), _username(src._username), _id(src._id), _command(src._command)
{}

User & User::operator=(const User &src)
{
	this->_nickname = src._nickname;
	this->_username = src._username;
    this->_socket = src._socket;
    this->_id = src._id;
    this->_command = src._command;
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

void    User::appendCommand(const std::string &str)
{
    _command += str;
}

std::string User::deliverCommand(void)
{
    std::string commandDelivered;
    size_t found = _command.find("\r\n");
    if (found != std::string::npos)
    {
        commandDelivered.assign(_command, 0, found);
        _command.erase(0, found + 2);
    }
    return (commandDelivered);
}

const std::string &User::getCommand(void) const
{
    return (_command);
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