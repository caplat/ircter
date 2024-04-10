#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <poll.h>
#include <list>
#include <cstring>
#include <map>



class User
{
    private:
        std::string _name, _pass, _userMode;
        int _so;
        std::list<std::string> _chan;
        std::string _str;
        pollfd _fd;
        int _regis;
    public:
        User(int);
        ~User();
        int getsock();
        std::string& getstr();
        int getregis();
        pollfd& getpollfd();

        void setstr(char*);

        void registration();

};

#endif