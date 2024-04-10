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
    size_t _end;

    do
    {
        _end = _str.find("\r\n");
        std::cout << "index of \\r\\n : " << _end << std::endl;
        if (_str.compare(0, 4,"NICK") != std::string::npos)
        {
            std::cout << "setup nickname, user, realname\n";
            _name = "userTest";
            _str.clear();
        }
        else if (_str.compare(0, 4, "USER") != std::string::npos)
        {
            std::cout << "The registration is finished\n"; 
            _regis = 1;
        }
		else
			_str.erase(0, _end);
    } while (_end != std::string::npos);
}