/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:33:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/14 11:46:15 by amarchal         ###   ########.fr       */
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
		std::map<int, User>	_operList;
		std::string			_topic;
		std::string			_mode;
		std::map<int, User>	_userList;

	public:
		// Channel();
		Channel(const Channel &src);
		Channel & operator=(const Channel &src);
		~Channel(void);

		Channel(std::string name, User & oper);
		void		setName(std::string name);
		void		setOperList(std::map<int, User> operList);
		std::string getName(void) const;
		std::map<int, User>	&getOperList(void);
		std::map<int, User> &getUserList(void);
};

#endif
