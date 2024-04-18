#include "User.hpp"

User::User(int fd, Server &_serv) : _so(fd), _regis(0), _server(&_serv){
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

Server* User::getServer()
{
    return (_server);
}


void User::setstr(char * str)
{
    _str.append(str);
}

void User::registration()
{
    size_t _end;

    {
        try
		{
       		_end = _str.find("\r\n");
       		if (_end == std::string::npos)
       		    throw(-1);
			cmds();
        }
        catch (int test)
        {
            std::cout << test << std::endl;
        }
		if (_end != std::string::npos)
			_str.erase(0, _end + 2);
    } 
}

void User::test()
{
	setup_nick();
}

int User::find_cmds()
{
	const char* tab[] = {"NICK", "USER"};
	std::list<std::string> _cmds(tab, tab + sizeof(tab) / sizeof(char*) );
	std::list<std::string>::iterator _it;
	int i = 0;
	for (_it = _cmds.begin(); _it != _cmds.end(); _it++)
	{
		if (_str.compare(0, 4, *_it) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void User::cmds()
{	
	switch (find_cmds())
	{
	case 0:
	{
            setup_nick();
			if (_regis)
			{
				std::cout << "The registration is finished\n"; 
				_server->sendfds_serv(_so, RPL_001(_server, _name));
				_server->sendfds_serv(_so, RPL_002(_server));
				_server->sendfds_serv(_so, RPL_003(_server));
				_server->sendfds_serv(_so, RPL_004(_server));
			}
			break;
	}
    case 1:
	{
            setup_user();
			if (_regis)
			{
				std::cout << "The registration is finished\n"; 
				_server->sendfds_serv(_so, RPL_001(_server, _name));
				_server->sendfds_serv(_so, RPL_002(_server));
				_server->sendfds_serv(_so, RPL_003(_server));
				_server->sendfds_serv(_so, RPL_004(_server));
			}
            break ;	
	}
	default:
		break;
	}
}

void User::setup_nick()
{
    size_t _index = _str.find(" ");
    size_t _len = 0;
	std::string _valid = "\\[]{}";
	if (_index == _str.size() -3 || _index == std::string::npos || isdigit(_str[_index + 1]))
	{
		std::cout << "you forgot the parameter" << std::endl;
		return ;
	}
    while (++_index < _str.size() - 2)
    {
        if(!isalnum(_str[_index]) && std::find(_valid.begin(), _valid.end(), _str[_index]) == _valid.end())
        {
            std::cout << "Error nickname\n";
            return ;
        }
        _len++;
    }
	std::cout << "Setup NICK\n";
    _name.append(_str, _str.find(" ") + 1, _len);
    if (!_name.empty() && !_username.empty())
        _regis = 1;

       
}

void User::setup_user()
{
    size_t _usern = 0;
    size_t _rn = 0;
	size_t _index = _str.find(" ");
	if (_index == _str.size() -2 || _index == std::string::npos)
	{
		std::cout << "you forgot the parameter" << std::endl;
		return ;
	}
	std::cout << "first space : " <<_index << std::endl;
	while(isalpha(_str[++_index]))
        _usern++;
 	_index = _str.find(" ", _index);
	std::cout << "second space : " <<_index << std::endl;
	if (_str[++_index] != '0')
		return ;
	_index = _str.find(" ", _index);
	std::cout << "third space : " <<_index << std::endl;
	if (_str[++_index] != '*')
		return ;
	_index = _str.find(" ", _index);
	std::cout << "fourth space : " <<_index << std::endl;
	while(isalpha(_str[++_index]) || isspace(_str[_index]))
        _rn++;
	if(_usern > 0 && _rn > 0)
	{
		std::cout << "Setup username \t realname\n";
 		_username.append(_str, _str.find(" ") + 1, _usern);
 		_realname.append(_str, _str.find(" ") + 1, _usern);
	}
	if(!_name.empty() && !_username.empty())
		_regis = 1;
}