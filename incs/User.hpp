/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:03 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/13 15:50:59 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include "ircserv.hpp"

class User
{
	private:
		int				_socket;
		std::string		_passwd;
		std::string 	_nickname;
		std::string 	_username;
		std::string 	_realname;
		unsigned int	_id;
        std::string     _command;
		std::string		_hostname;

	public:
		User(void);
		User(const User &src);
		User & operator=(const User &src);
		~User(void);
		
		User(std::string nickname, std::string username, unsigned int id);
		void					setSocket(int socket);
		void					setPasswd(std::string passwd);
		void					setNickname(std::string nickname);
		void					setUsername(std::string username);
		void					setRealname(std::string realname);
		void					setId(unsigned int id);
		void					setHostname(std::string hostname);
		int						getSocket(void) const;
		std::string 			getPasswd(void) const;
		std::string 			getNickname(void) const;
		std::string 			getUsername(void) const;
		std::string 			getRealname(void) const;
		unsigned int			getId(void) const;
		std::string				getHostname(void) const;
        void            		appendCommand(const std::string &str);
        const std::string		&getCommand(void) const;
        std::string     		deliverCommand(void);
};
std::ostream 	&operator<<(std::ostream &stream, const User &source);

#endif