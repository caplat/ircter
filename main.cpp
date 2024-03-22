#include <iostream>
#include <sys/socket.h> /* Tout ce qui est lie aux socket*/
#include <netinet/in.h> /* sockaddr_in*/
#include <cstdlib>
#include <sys/types.h> /* Utilise certaines macros */
#include <netdb.h> /* gethostbyname*/
#include <errno.h>
#include <cstring> /*std::strerror*/
#include <unistd.h> /* */


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

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    
   addrinfo *_host;
   _host = NULL;
   set_addrinfo(&_host);

    std::cout << _host->ai_protocol << std::endl;
    int _sock = socket(_host->ai_family, _host->ai_socktype, _host->ai_protocol);
    if (_sock == -1)
    {
        std::cout << errno << std::strerror(errno) << std::endl;
        return (-1);
    }
}