#include "User.hpp"

User::User(int fd) : _so(fd), _regis(0){
    _fd.fd = fd;
    _fd.events = POLLIN;
}

User::~User()
{}

int User::getsock()
{
    return (_so);
}

int User::getregis()
{
    return (_regis);
}

char* User::getbuff()
{
    return (_buff);
}

std::string User::getstr()
{
    return (_str);
}

pollfd& User::getpollfd()
{
    return (_fd);
}


void User::setstr(char * str)
{
    _str.append(str);
}