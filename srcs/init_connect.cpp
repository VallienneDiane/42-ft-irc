#include "../incs/ircserv.hpp"

int capMsg(const int socket)
{
    std::string str = SERVER_TALKING;
    str += "CAP * LS :";
    return sendMsg(socket, str);
}

int welcomeMsg(const int socket)
{
    std::string str = SERVER_TALKING;
    str += "001 njaros ";
    str += SERVER_DESCRIPTION;
    str += " njaros!";
    return sendMsg(socket, str);
}