/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:49:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/17 16:57:50 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Channel.hpp"

/****************** CANONIC FORM ******************/
Channel::Channel(const Channel &src) : _name(src._name), _operSet(src._operSet), _userSet(src._userSet)
{}

// Channel::Channel(void)
// {}

Channel & Channel::operator=(const Channel &src)
{
	this->_name = src._name;
	this->_operSet = src._operSet;
	this->_userSet = src._userSet;
	return (*this);
}

Channel::~Channel(void)
{}

/****************** CONSTRUCTOR BY NAME ******************/
Channel::Channel(std::string name, User &oper) : _name(name)
{
	this->_operSet.insert(oper.getSocket());
}

/****************** SETTERS ******************/
void	Channel::setName(std::string name)
{
	this->_name = name;
}

void	Channel::setOperSet(std::set<int> operSet)
{
	this->_operSet = operSet;
}

/****************** GETTERS ******************/
std::string Channel::getName(void) const
{
	return (this->_name);
}

std::set<int> &Channel::getOperSet(void)
{
	return (this->_operSet);
}

std::set<int> &Channel::getUserSet(void)
{
	return (this->_userSet);
}

/***************** MEMBER OPERANDS ***************/

void	Channel::addUser(User &user) {
	_userSet.insert(user.getSocket());
}

void	Channel::addUser(int userSocket) {
	_userSet.insert(userSocket);
}

void	Channel::delUser(User &user) {
	_userSet.erase(user.getSocket());
}

void	Channel::delUser(int userSocket) {
	_userSet.erase(userSocket);
}

void	Channel::addOper(User &user) {
	_operSet.insert(user.getSocket());
}

void	Channel::addOper(int userSocket) {
	_operSet.insert(userSocket);
}

void	Channel::delOper(User &user) {
	_operSet.erase(user.getSocket());
}

void	Channel::delOper(int userSocket) {
	_operSet.erase(userSocket);
}

std::pair<bool, std::set<int>::iterator>	Channel::isInUserSet(User &user) {
	return (this->isInUserSet(user.getSocket()));
}

std::pair<bool, std::set<int>::iterator>	Channel::isInUserSet(int userSocket) {
	std::set<int>::iterator	found = _userSet.find(userSocket);
	if (found != _userSet.end())
		return (std::make_pair(true, found));
	return (std::make_pair(false, found));
}

std::pair<bool, std::set<int>::iterator>	Channel::isInOperSet(User &user) {
	return (this->isInOperSet(user.getSocket()));
}

std::pair<bool, std::set<int>::iterator>	Channel::isInOperSet(int userSocket) {
	std::set<int>::iterator	found = _operSet.find(userSocket);
	if (found != _operSet.end())
		return (std::make_pair(true, found));
	return (std::make_pair(false, found));
}