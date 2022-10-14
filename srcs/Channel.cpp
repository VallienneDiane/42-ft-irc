/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:49:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/14 13:57:19 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Channel.hpp"

/****************** CANONIC FORM ******************/
Channel::Channel(const Channel &src) : _name(src._name), _operList(src._operList), _userList(src._userList)
{}

// Channel::Channel(void)
// {}

Channel & Channel::operator=(const Channel &src)
{
	this->_name = src._name;
	this->_operList = src._operList;
	this->_userList = src._userList;
	return (*this);
}

Channel::~Channel(void)
{}

/****************** CONSTRUCTOR BY NAME ******************/
Channel::Channel(std::string name, User &oper) : _name(name)
{
	this->_operList.insert(std::pair<int, User>(oper.getSocket(), oper));
}

/****************** SETTERS ******************/
void	Channel::setName(std::string name)
{
	this->_name = name;
}

void	Channel::setOperList(std::map<int, User> operList)
{
	this->_operList = operList;
}

/****************** GETTERS ******************/
std::string Channel::getName(void) const
{
	return (this->_name);
}

std::map<int, User>  &Channel::getOperList(void)
{
	return (this->_operList);
}

std::map<int, User> &Channel::getUserList(void)
{
	return (this->_userList);
}

/***************** MEMBER OPERANDS ***************/

void	Channel::addUser(User &user) {
	_userList.insert(std::make_pair(user.getSocket(), user));
}

void	Channel::delUser(User &user) {
	_userList.erase(user.getSocket());
}

void	Channel::delUser(int userSocket) {
	_userList.erase(userSocket);
}

void	Channel::addOper(User &user) {
	_operList.insert(std::make_pair(user.getSocket(), user));
}

void	Channel::delOper(User &user) {
	_operList.erase(user.getSocket());
}

void	Channel::delOper(int userSocket) {
	_operList.erase(userSocket);
}