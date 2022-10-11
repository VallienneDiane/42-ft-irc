/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:03 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/11 11:06:14 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include "ircserv.hpp"

class User
{
	private:
		int				_socket;
		std::string 	_nickname;
		std::string 	_username;
		unsigned int	_id;
        std::string     _command;

	public:
		User(void);
		User(const User &src);
		User & operator=(const User &src);
		~User(void);
		
		User(std::string nickname, std::string username, unsigned int id);
		void			setSocket(int socket);
		void			setNickname(std::string nickname);
		void			setUsername(std::string username);
		void			setId(unsigned int id);
		int				getSocket(void) const;
		std::string 	getNickname(void) const;
		std::string 	getUsername(void) const;
		unsigned int	getId(void) const;
        void            appendCommand(const std::string &str);
        const std::string     &getCommand(void) const;
        std::string     deliverCommand(void);
};

std::ostream 	&operator<<(std::ostream &stream, const User &source);


#endif