#ifndef SERVER_HPP
#define SERVER_HPP
#include "Pollfds.hpp"
#include <sys/types.h> /* Utilise certaines macros */
#include <errno.h>
#include <netdb.h> /* gethostbyname*/
#include <map>
#include <list>

class User
{
    private:
        std::string _name;
        int _so;
        std::list<std::string> _chan;
    public:
        User(int fd) : _so(fd){}
        ~User(){}
        int getsock(){return (_so);}
    friend std::ostream& operator<<(std::ostream & f, std::map<std::string, User> &s)
{
    for (std::map<std::string, User>::iterator it = s.begin();   it != s.end(); it++)
    {
        f << it->first << std::endl; 
    }
    return (f);
}

};

class Server
{
    private:
    addrinfo *_host;
    int _sock_serv;
    Poll_fds _fds;
    std::map<std::string, User> _users;

    public:
    Server();
    ~Server();
    void set_host();
    void make_sockserv();
    int getsock_serv();
    addrinfo& getaddrinfo_serv();
    Poll_fds& getpollfd_serv();
    void run_serv();
    void accept_conection_serv();
    void readfds_serv(int);
};

#endif