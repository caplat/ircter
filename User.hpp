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
        //std::string _name;
        int _so;
        //std::list<std::string> _chan;
        char _buff[100];
        std::string _str;
        pollfd _fd;
        int _regis;
    public:
        User(int);
        ~User();
        int getsock();
        char* getbuff();
    std::string getstr();
        int getregis();
        pollfd& getpollfd();

        void setstr(char*);

};

#endif