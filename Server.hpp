#ifndef SERVER_HPP
#define SERVER_HPP
#include "User.hpp"
#include <iostream>
#include <vector>
#include <sys/types.h> /* Utilise certaines macros */
#include <unistd.h> /* */
#include <errno.h>
#include <netdb.h> /* gethostbyname*/
#include <utility>
#define _BUFF_SIZE 20
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
    std::map<int, User>& getUsers();
    User* findUser(int);

    void makepollfd_fds();
    void make_sockserv();

    void run_serv();
    void readfds_serv(int);
    void accept_conection_serv();
};
std::ostream& operator<<(std::ostream&, Server&); 

#endif