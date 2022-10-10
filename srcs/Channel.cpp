/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:49:16 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/07 14:15:10 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Channel.hpp"

/****************** CANONIC FORM ******************/

Channel::Channel(const Channel &src) : _name(src._name), _founder(src._founder)
{}

Channel & Channel::operator=(const Channel &src)
{
	this->_name = src._name;
	this->_founder = src._founder;
	return (*this);
}

Channel::~Channel(void)
{}

/****************** CONSTRUCTOR BY NAME ******************/
Channel::Channel(std::string name, User & founder) : _name(name), _founder(founder)
{}

/****************** SETTERS ******************/
void	Channel::setName(std::string name)
{
	this->_name = name;
}

void	Channel::setFounder(User & founder)
{
	this->_founder = founder;
}

/****************** GETTERS ******************/
std::string Channel::getName(void) const
{
	return (this->_name);
}

User & Channel::getFounder(void) const
{
	return (this->_founder);
}
