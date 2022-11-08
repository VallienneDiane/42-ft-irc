/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:42:03 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/19 13:43:04 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP
# include "ircserv.hpp"

class User
{
	private:
		int							_socket;
		std::string					_passwd;
		std::string 				_nickname;
		std::string 				_username;
		std::string 				_realname;
		bool						_pass;
		unsigned int				_id;
        std::string     			_command;
		std::string					_hostname;
		std::set<std::string> 		_channels;
		std::set<int> 				_privMsg;
		std::vector<std::string>	_bufferMsg;

	public:
		User(void);
		User(std::string nickname, std::string username, unsigned int id);
		User(const User &src);
		User & operator=(const User &src);
		~User(void);
		
		///////// [SETTERS]
		void						setSocket(int socket);
		void						setPasswd(std::string passwd);
		void						setNickname(std::string nickname);
		void						setUsername(std::string username);
		void						setRealname(std::string realname);
		void						setId(unsigned int id);
		void						setHostname(std::string hostname);
		void						setPassOk(void);
		
		///////// [GETTERS]
		int							getSocket(void) const;
		std::string 				getPasswd(void) const;
		std::string 				getNickname(void) const;
		std::string 				getUsername(void) const;
		std::string 				getRealname(void) const;
		bool						getPass() const;
		unsigned int				getId(void) const;
		std::string					getHostname(void) const;
		std::set<std::string>		&getChannels(void);
		std::set<int>				&getPrivMsg(void);
		std::vector<std::string>	&getBufferMsg(void);
		
		///////// [MEMBER FUNCTIONS]
        void            			appendCommand(const std::string &str);
        const std::string			&getCommand(void) const;
        std::string     			deliverCommand(void);
		void						addChannel(std::string channelName);
		void						addPrivMsg(int userSocket);
		void						removeChannel(std::string channelName);
		void						removePrivMsg(int userSocket);
		bool						isInPrivMsg(int userSocket);
		void						addMsgToBuffer(std::string &msg);
		void						addMsgToBuffer(std::string const &msg) ;
		bool						deliverBufferMsg(void);
};

std::ostream 						&operator<<(std::ostream &stream, const User &source);
bool								fullyRegistered(const User &user);
std::map<int, User>::iterator		findUserByNickName(const std::string &nick, std::map<int, User> &userMap);

#endif