/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:33:51 by dvallien          #+#    #+#             */
/*   Updated: 2022/10/07 14:46:38 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include "ircserv.hpp"
# include "User.hpp"

class Channel
{
	private:
		Channel(void);
		std::string		_name;
		User &			_founder;
		std::string		_topic;
		std::string		_mode;

	public:
		Channel(const Channel &src);
		Channel & operator=(const Channel &src);
		~Channel(void);

		Channel(std::string name, User & founder);
		void		setName(std::string name);
		void		setFounder(User & founder);
		std::string getName(void) const;
		User &		getFounder(void) const;
};

#endif
