#include <iostream>
#include <sys/socket.h> /* Tout ce qui est lie aux socket*/
#include <netinet/in.h> /* sockaddr_in*/
#include <cstdlib>
#include <sys/types.h> /* Utilise certaines macros */
#include <netdb.h> /* gethostbyname*/
#include <errno.h>
#include <cstring> /*std::strerror*/
#include <unistd.h> /* */
#include <vector>
#include <poll.h>
void set_addrinfo(addrinfo **h)
{
    addrinfo _init;
    memset(&_init, 0, sizeof _init);
    _init.ai_family = AF_INET;
    _init.ai_flags = AI_PASSIVE;
    _init.ai_socktype = SOCK_STREAM;

    int _test = getaddrinfo(0, "4263", &_init, &(*h));
    std::cout << _test << std::endl;
    if (_test != 0)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return ;
    }
    else
        std::cout << "Getaddrinfo is ok" << std::endl;
}

pollfd create_pullfd(int fd, short events)
{
    pollfd b;
    b.fd = fd;
    b.events = events;
    return (b);
}

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    
   addrinfo *_host;
   _host = NULL;
   set_addrinfo(&_host);

    int _sock = socket(_host->ai_family, _host->ai_socktype, _host->ai_protocol);
    if (_sock == -1)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return (-1);
    }

    if (bind(_sock, _host->ai_addr, _host->ai_addrlen) != 0)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return (-1);
    }
    listen(_sock, 20);

    sockaddr _addr_cli;
    int _client_fd;
    socklen_t _size_cli = sizeof(_addr_cli);

    _client_fd = accept(_sock, &_addr_cli, &_size_cli);
    if (_client_fd == -1)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return (-1);
    }
    else
        std::cout << "New connection" << std::endl;


    std::vector<pollfd> _poll_fds;

     _poll_fds.push_back(create_pullfd(_sock, POLLIN));

    std::string  _buffer;
    char _buff_read[100];
    std::string _content;
    long _bytes_r = 0;
    do
    {
        _bytes_r = recv(_client_fd, _buff_read, 100, 0);
        _buff_read[_bytes_r] = 0;
        if (_bytes_r > 0)
        {
            _content.append(_buff_read);
            bzero(_buff_read, 100);
            std::cout << _content << std::endl;
        }
    }
    while (_bytes_r > 0);
    _buffer = "HELLO WORD !";
    size_t _bytes = 0;
    size_t _size_buffer = _buffer.size();
    while (_bytes != _size_buffer) 
    {
        _bytes += send(_client_fd, &(_buffer[_bytes]), _size_buffer, 0);
    }
    std::cout << _bytes << std::endl;
    close(_sock);
    close(_client_fd);
}