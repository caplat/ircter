#ifndef SERVER_HPP
#define SERVER_HPP
#include "Pollfds.hpp"
#include <netdb.h> /* gethostbyname*/


class Server
{
    private:
    addrinfo *_host;
    int _sock_serv;

    public:
    Server();
    ~Server();
    void set_host();
    void make_sockserv();
    int getsock_serv();
    addrinfo& getaddrinfo_serv();
};


#endif