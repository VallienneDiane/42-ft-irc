/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:33:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/17 15:54:40 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "ircserv.hpp"
# include "User.hpp"

class User;

class Channel
{
	private:
		// Channel(void);
		std::string				_name;
		std::set<int>			_operSet;
		// std::map<int, User>	_operList;
		std::string				_topic;
		std::string				_mode;
		std::set<int>			_userSet;
		// std::map<int, User>	_userList;

	public:
		// Channel();
		Channel(const Channel &src);
		Channel & operator=(const Channel &src);
		~Channel(void);

		Channel(std::string name, User & oper);
		void		setName(std::string name);
		// void		setOperList(std::map<int, User> operList);
		void		setOperSet(std::set<int> operSet);
		std::string getName(void) const;
		// std::map<int, User>	&getOperList(void);
		// std::map<int, User> &getUserList(void);
		std::set<int>		&getOperSet(void);
		std::set<int>		&getUserSet(void);
		void		addUser(User &user);
		void		addUser(int userSocket);
		void		delUser(User &user);
		void		delUser(int userSocket);
		void		addOper(User &user);
		void		addOper(int userSocket);
		void		delOper(User &user);
		void		delOper(int userSocket);
		// void		addUser(User &user);
		// void		delUser(User &user);
		// void		delUser(int userSocket);
		// void		addOper(User &user);
		// void		delOper(User &user);
		// void		delOper(int userSocket);
		// std::pair<bool, std::map<int, User>::iterator>	isInUserList(User &user);
		// std::pair<bool, std::map<int, User>::iterator>	isInUserList(int userSocket);
		// std::pair<bool, std::map<int, User>::iterator>	isInOperList(User &user);
		// std::pair<bool, std::map<int, User>::iterator>	isInOperList(int userSocket);
		std::pair<bool, std::set<int>::iterator>	isInUserSet(User &user);
		std::pair<bool, std::set<int>::iterator>	isInUserSet(int userSocket);
		std::pair<bool, std::set<int>::iterator>	isInOperSet(User &user);
		std::pair<bool, std::set<int>::iterator>	isInOperSet(int userSocket);
		void	sendToUsers(const std::string &content, int socketException) const;
};

#endif
