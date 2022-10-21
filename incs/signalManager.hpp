#ifndef SIGNAL_MANAGER
# define SIGNAL_MANAGER

# include <csignal>
# include <sys/socket.h>
# include <unistd.h>

void    signalOn(int servSocket);
void    signalHandler(int sig, siginfo_t *siginfo, void *ucontext);
int     setGiveSocket(int valSocket);

#endif