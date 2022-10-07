#include "../incs/ircserv.hpp"

int main() {
    protoent    *protocol;
    protocol = getprotobyname("ip");
    sockaddr_in sockAdr;
    long int r;
    int socketT = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
    sockAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAdr.sin_family = PF_INET;
    sockAdr.sin_port = htons(6667);
    if (bind(socketT, reinterpret_cast<sockaddr *>(&sockAdr), sizeof(sockAdr)))
        std::cout << "bind failed because : " <<  strerror(errno) << std::endl;
    std::cout << "server socket is : " << socketT << std::endl;
    if (listen(socketT, 10))
        std::cout << "listen failed because : " << strerror(errno) << std::endl;
    sockaddr_in clientSockInfo;
    socklen_t len = clientSockInfo.sin_len;
    int sockIn = accept(socketT, reinterpret_cast<sockaddr *>(&clientSockInfo), &len);
    if (sockIn < 0)
        std::cout << "accept failed because : " << strerror(errno) << std::endl;
    else {
        protocol = getprotobynumber(clientSockInfo.sin_family);
        std::cout << "The family client is : " << protocol->p_name << "\nthe addr client is : " << inet_ntoa(clientSockInfo.sin_addr)
                  << std::endl << "the id client is : " << sockIn << std::endl;
        std::string buffer;
        for (int i = 0; i < 3; ++i)
        {
            r = receiveMsg(sockIn, buffer);
            switch (r) {
                case -1:
                    close(socketT);
                    exit(errno);
                case 0:
                    close(socketT);
                    exit(0);
                default:
                    std::cout << "client said : " << buffer;
            }
        }
        if (sendMsg(sockIn, "CAP * LS :\r\n") == -1)
            std::cout << "send failed because : " << strerror(errno) << std::endl;
        r = receiveMsg(sockIn, buffer);
        switch (r) {
            case -1:
                close(socketT);
                exit(errno);
            case 0:
                close(socketT);
                exit(0);
            default:
                std::cout << "client said : " << buffer;
        }
    }
    close(socketT);
    return 0;
}
