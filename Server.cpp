#include "Server.hpp"

Server::Server()
{
    set_host();
}

Server::~Server()
{
    freeaddrinfo(_host);
}

void Server::set_host()
{
    addrinfo _init;
    memset(&_init, 0, sizeof _init);
    _init.ai_family = AF_INET;
    _init.ai_flags = AI_PASSIVE;
    _init.ai_socktype = SOCK_STREAM;

    int _test = getaddrinfo(0, "4263", &_init, &_host);
    std::cout << _test << std::endl;
    if (_test != 0)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return ;
    }
    else
        std::cout << "Getaddrinfo is ok" << std::endl;
}

void Server::make_sockserv()
{
    _sock_serv = socket(_host->ai_family, _host->ai_socktype, _host->ai_protocol);
    if (_sock_serv == -1)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        throw ;
    }
}

int Server::getsock_serv()
{
    return (_sock_serv);
}

addrinfo& Server::getaddrinfo_serv()
{
    return (*_host);
}