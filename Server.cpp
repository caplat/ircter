#include "Server.hpp"

Server::Server()
{
    set_host();
    make_sockserv();
}

Server::~Server()
{
    freeaddrinfo(_host);
    close(_sock_serv);
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
        throw -2;
    }
    _fds.new_fds(_sock_serv, POLLIN);
}

int Server::getsock_serv()
{
    return (_sock_serv);
}

addrinfo& Server::getaddrinfo_serv()
{
    return (*_host);
}

Poll_fds& Server::getpollfd_serv()
{
    return (_fds);
}

void Server::accept_conection_serv()
{
    int _fdcli;
    sockaddr _addr_cli;
    socklen_t _size_cli = sizeof(_addr_cli);
    _fdcli = accept(_sock_serv, &_addr_cli, &_size_cli);

    User _new(_fdcli);
    std::string _str = "name";
    _users.insert(std::make_pair(_str, _new));
    std::cout << _users << std::endl;
    _fds.new_fds(_fdcli, POLLIN);
    std::cout << _fds << std::endl;
}

void Server::readfds_serv(int fd)
{
    std::string  _buffer;
    char _buff_read[100];
    std::string _content;
    long _bytes_r = 0;
    _bytes_r = recv(fd, _buff_read, 100, 0);
    _buff_read[_bytes_r] = 0;
    if (_bytes_r > 0)
    {
        _content.append(_buff_read);
        bzero(_buff_read, 100);
        std::cout << _content << std::endl;
    }
}

void Server::run_serv()
{
    if (bind(_sock_serv, _host->ai_addr, _host->ai_addrlen) != 0)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        throw -1;
    }
    listen(_sock_serv, 20);
    while (1)
    {
        int status = poll(_fds.getpollfd_fds(), _fds.getsize_fds(), 2000);
        if(status  == 0 || status == -1)
        {
            std::cout << "Server waitting..." << "status : " << status << std::endl;
            continue ;
        }
        else if(_fds.fdpollin_fds() != -1)
        {
            int _fd = _fds.fdpollin_fds();
             if (_fd == _sock_serv)
             {
                accept_conection_serv();
             }
             else
                readfds_serv(_fd);
        }
    }
}