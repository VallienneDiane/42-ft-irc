/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:33:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/19 13:46:55 by amarchal         ###   ########.fr       */
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
		std::string			_name;
		std::string			_key;
		bool				_hasKey;
		std::string			_topic;
		bool				_isTopicSet;
		std::set<int>		_operSet;
		std::string			_mode;
		std::set<int>		_userSet;

	public:
		// Channel();
		Channel(const Channel &src);
		Channel & operator=(const Channel &src);
		~Channel(void);

		Channel(std::string name, User & oper);
		void				setTopic(std::string topic);
		std::string 		getTopic(void) const;
		bool		 		getIsTopicSet(void) const;
		void				setName(std::string name);
		void				setKey(std::string key);
		bool				hasKey(void) const;
		void				setOperSet(std::set<int> operSet);
		std::string 		getName(void) const;
		std::string 		getKey(void) const;
		std::set<int>		&getOperSet(void);
		std::set<int>		&getUserSet(void);
		void				addUser(User &user);
		void				addUser(int userSocket);
		void				delUser(User &user);
		void				delUser(int userSocket);
		void				addOper(User &user);
		void				addOper(int userSocket);
		void				delOper(User &user);
		void				delOper(int userSocket);
		std::pair<bool, std::set<int>::iterator>	isInUserSet(User &user);
		std::pair<bool, std::set<int>::iterator>	isInUserSet(int userSocket);
		std::pair<bool, std::set<int>::iterator>	isInOperSet(User &user);
		std::pair<bool, std::set<int>::iterator>	isInOperSet(int userSocket);
		std::string			userCount(void);
		void	sendToUsers(const std::string &content, int socketException, std::map<int, User> &userMap) const;
};

#endif
