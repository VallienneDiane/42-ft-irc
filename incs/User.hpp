/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:03 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/07 14:45:46 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include "ircserv.hpp"

class User
{
	private:
		std::string 	_nickname;
		std::string 	_username;
		unsigned int	_id;

	public:
		User(void);
		User(const User &src);
		User & operator=(const User &src);
		~User(void);
		
		User(std::string nickname, std::string username, unsigned int id);
		void			setNickname(std::string nickname);
		void			setUsername(std::string username);
		void			setId(unsigned int id);
		std::string 	getNickname(void) const;
		std::string 	getUsername(void) const;
		unsigned int	getId(void) const;
};

#endif