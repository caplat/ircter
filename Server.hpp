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
        pollfd _fd;
    public:
        User(int fd) : _so(fd){
            _fd.fd = fd;
            _fd.events = POLLIN;
        }
        ~User(){}
        int getsock(){return (_so);}
        pollfd& getpollfd(){return (_fd);}

};

typedef  std::map<int, User>::iterator _ituser;
class Server
{
    private:
    addrinfo *_host;
    int _sock_serv;
    std::map<int, User> _users;
    pollfd* _poll;
    size_t _size_poll;

    public:
    Server();
    ~Server();
    void set_host();
    addrinfo& getaddrinfo_serv();

    int getsock_serv();
    int getRevents();
    std::map<int, User> getUsers();

    void makepollfd_fds();
    void make_sockserv();

    void run_serv();
    void readfds_serv(int);
    void accept_conection_serv();
};
std::ostream& operator<<(std::ostream&, Server&); 

#endif