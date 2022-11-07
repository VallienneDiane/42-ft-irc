/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:21:34 by njaros            #+#    #+#             */
/*   Updated: 2022/11/07 13:21:34 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER
# define SIGNAL_MANAGER

# include <csignal>
# include <sys/socket.h>
# include <unistd.h>
 #include <sys/select.h>
 
void    signalOn(int servSocket);
void    signalHandler(int sig, siginfo_t *siginfo, void *ucontext);
int     setGiveSocket(int valSocket);

#endif