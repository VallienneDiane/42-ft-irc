#include "../incs/ircserv.hpp"

int assignReadValue(int &a, int b)
{
    a = b;
    return b;
}

int receiveMsg(int socket, std::string &buffer)
{
    buffer.clear();
    char    c;
    int     rd;
    std::string::size_type  size = 0;
    while (assignReadValue(rd, recv(socket, &c, 1, 0)) && rd != -1)
    {
        buffer += c;
        size += 1;
        if (buffer.size() >= 2 &&
                (buffer[size - 2] == '\r' && buffer[size - 1] == '\n'))
            return (buffer.size());
        if (buffer[size - 1] == '\0')
            std::cout << "je me suis trompé\n";
    }
    switch (rd)
    {
        case -1:
            std::cout << "recv failed because : " << strerror(errno) << std::endl;
            break ;
        default:
            std::cout << "end of communication with socket " << socket << std::endl;
    }
    return 0;
}
