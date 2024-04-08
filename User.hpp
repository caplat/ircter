#ifndef USER_HPP
#define USER_HPP
#include <poll.h>
#include <list>
#include <cstring>
#include <map>

class User
{
    private:
        //std::string _name;
        int _so;
        //std::list<std::string> _chan;
        pollfd _fd;
    public:
        User(int);
        ~User();
        int getsock();
        pollfd& getpollfd();

};

#endif