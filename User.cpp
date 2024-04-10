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

    {
        _end = _str.find("\r\n");
        std::cout << "index of \\r\\n : " << _end << std::endl;
        std::cout << _str << std::endl;
        if (_str.compare(0, 4,"NICK") == 0 && _end != std::string::npos)
        {
            std::cout << "setup nickname, user, realname\n";
            _name = "userTest";
        }
        else if (_str.compare(0, 4, "USER") == 0 && _end != std::string::npos)
        {
            std::cout << "The registration is finished\n"; 
            _regis = 1;
        }
		if (_end != std::string::npos)
			_str.erase(0, _end + 2);
    } 
}