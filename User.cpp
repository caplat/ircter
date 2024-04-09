#include "User.hpp"

User::User(int fd) : _so(fd), _regis(0), CAPLS(0){
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

std::string& User::getstr()
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

void User::registration()
{
    if(!CAPLS && _str.find("CAP LS") != std::string::npos)
    {
        std::cout << "CAP LS :" << std::endl;
        CAPLS = 1;
        _str.erase(_str.begin());
    }
    else if (CAPLS && _name.empty())
    {
        std::cout << "setup nickname, user, realname\n";
        _name = "userTest";
        _str.erase(_str.begin());
    }
    else if (CAPLS && _str.find("CAP END") && !_name.empty())
    {
        std::cout << "The registration is finished\n"; 
        _regis = 1;
    }
    
}