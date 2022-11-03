/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:14:30 by dvallien          #+#    #+#             */
/*   Updated: 2022/11/03 10:14:30 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER
# define SIGNAL_MANAGER

# include <csignal>
# include <sys/socket.h>
# include <unistd.h>

void    signalOn(int servSocket);
void    signalHandler(int sig, siginfo_t *siginfo, void *ucontext);
int     setGiveSocket(int valSocket);

#endif