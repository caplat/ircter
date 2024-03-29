#include <iostream>
#include <sys/types.h> /* Utilise certaines macros */
#include <netinet/in.h> /* sockaddr_in*/
#include <sys/socket.h> /* Tout ce qui est lie aux socket*/
#include <errno.h>
#include <cstring> /*std::strerror*/
#include <vector>
#include "Pollfds.hpp"
#include "Server.hpp"



int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    
   addrinfo *_host;
   _host = NULL;
   Server _s;



    if (bind(_s.getsock_serv(), _host->ai_addr, _host->ai_addrlen) != 0)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return (-1);
    }
    listen(_sock, 20);

    short int _events[] = {POLLIN};
    Poll_fds _fds(&_sock, 1, _events);
    std::cout << _fds << std::endl;

    std::string  _buffer;
    char _buff_read[100];
    std::string _content;
    long _bytes_r = 0;
    int _client_fd;
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
             if (_fds.fdpollin_fds() == _sock)
             {
                sockaddr _addr_cli;
                socklen_t _size_cli = sizeof(_addr_cli);
                _client_fd = accept(_sock, &_addr_cli, &_size_cli);
                _fds.new_fds(_client_fd, POLLIN);
                std::cout << _fds << std::endl;

             }
             else
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
        }
    }
    close(_sock);
    close(_client_fd);
}