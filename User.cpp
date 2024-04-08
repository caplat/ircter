#include "User.hpp"

User::User(int fd) : _so(fd){
    _fd.fd = fd;
    _fd.events = POLLIN;
}

User::~User()
{}

int User::getsock()
{
    return (_so);
}

pollfd& User::getpollfd()
{
    return (_fd);
}