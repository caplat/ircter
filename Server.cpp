#include "Server.hpp"

Server::Server()
{
    _poll = NULL;
    _size_poll = 0;
    set_host();
    make_sockserv();
}

Server::~Server()
{
    freeaddrinfo(_host);
    delete _poll;
    close(_sock_serv);
}

void Server::set_host()
{
    addrinfo _init;
    memset(&_init, 0, sizeof _init);
    _init.ai_family = AF_INET;
    _init.ai_flags = AI_PASSIVE;
    _init.ai_socktype = SOCK_STREAM;
    int _test = getaddrinfo(0, "4264", &_init, &_host);
    std::cout << _test << std::endl;
    if (_test != 0)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return ;
    }
    else
        std::cout << "Getaddrinfo is ok" << std::endl;
    gethostname(_hostname, sizeof(_hostname));
    std::cout << (std::string)_hostname << std::endl;
}

void Server::make_sockserv()
{
    _sock_serv = socket(_host->ai_family, _host->ai_socktype, _host->ai_protocol);
    if (_sock_serv == -1)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        throw -2;
    }
    User _serv(_sock_serv, *this);
    _users.insert(std::make_pair(_sock_serv, _serv));
    makepollfd_fds();
}

int Server::getsock_serv()
{
    return (_sock_serv);
}

addrinfo& Server::getaddrinfo_serv()
{
    return (*_host);
}

void Server::accept_conection_serv()
{
    int _fdcli;
    sockaddr _addr_cli;
    socklen_t _size_cli = sizeof(_addr_cli);
    _fdcli = accept(_sock_serv, &_addr_cli, &_size_cli);
    User _new(_fdcli, *this);
    _users.insert(std::make_pair(_fdcli, _new));
    std::cout << *this << std::endl;
    makepollfd_fds();
}

void Server::readfds_serv(int fd)
{
    std::string  _buffer;
    char _buff_read[_BUFF_SIZE];
    User* _us = findUser(fd);
    std::string _content;
    long _bytes_r = 1;
    _bytes_r = recv(fd, _buff_read, _BUFF_SIZE, 0);
    if (_bytes_r == 0)
    {
        _users.erase(fd);
        close(fd);
        makepollfd_fds();
    }
    _buff_read[_bytes_r] = 0;
    if (_bytes_r > 0)
    {
        _content.append(_buff_read);
        _us->setstr(_buff_read);
        bzero(_buff_read, _BUFF_SIZE);
        if (_us->getstr().find("\r\n") != std::string::npos)
            std::cout << _us->getstr() << std::endl;
        
    }
    if (!_us->getregis())
    {
        std::cout << "Registration\n";
        _us->registration();
    }
}

void Server::sendfds_serv(int fd, std::string str)
{
    if(str.size() < 512)
    {
        send(fd, str.c_str(), str.size(), 0);
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
        int status = poll(_poll, _size_poll, 2000);
        if(status  == 0 || status == -1)
        {
            for (size_t i = 0; i < _size_poll; i++)
            {
                std::cout << _poll[i].revents << std::endl;
            }
            std::cout << "Server waitting..." << "status : " << status << std::endl;
            continue ;
        }
        else if (getRevents() > 0)
        {
            int _fd = getRevents();
             if (_fd == _sock_serv)
             {
                accept_conection_serv();
             }
             else
             {
                std::cout << "Read\n";
                for (size_t i = 0; i < _size_poll; i++)
                {
                    std::cout << _poll[i].revents << std::endl;
                }
                readfds_serv(_fd);
             }
        }
    }
}

int Server::getRevents()
{
    for (size_t i = 0; i < _size_poll; i++)
    {
        if(_poll[i].revents == POLLIN)
        {
            return (_poll[i].fd);
        }
    }
    
    return (-1);
}

std::map<int, User>& Server::getUsers()
{
    return (_users);
}

std::string Server::gethostname_srv()
{
    return ((std::string)_hostname);
}


void Server::makepollfd_fds()
{
    int i = 0;
    _poll = new pollfd[_users.size()];
    for(_ituser it = _users.begin(); it != _users.end(); it++)
    {
        _poll[i]= it->second.getpollfd();
        i++;
    }
    _size_poll = i;
    
}

User* Server::findUser(int fd)
{
    for (_ituser i = _users.begin(); i != _users.end(); i++)
    {
        if (i->first == fd)
        {
            return (&(i->second));
        }
    }
    std::cout << "User not Found\n";
    throw ;
}



//User
std::ostream& operator<<(std::ostream & f, Server &s) 
{
    std::map<int, User> _us = s.getUsers();
      for (_ituser it = _us.begin();   it != _us.end(); it++)
      {
          f << (it->second.getsock()) << std::endl; 
      }
      return (f);
}