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
			std::cout << "\\r\\n : " << _end << std::endl;
       		if (_end == std::string::npos)
       		    throw(-1);
			trim_cmds(_end);
			cmds_register();
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
	const char* tab[] = {"NICK", "USER", "PING"};
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

void User::cmds_register()
{	
	std::string _rpl[8] = {
		RPL_WELCOME(_server, _name), 
		RPL_YOURHOST(_server, _name),
		RPL_CREATED(_server, _name),
		RPL_MYINFO(_server, _name),
		RPL_ISUPPORT(_server, _name),
		RPL_MOTD(_server, _name),
		RPL_ENDOFMOTD(_server, _name),
		RPL_UMODEIS(_server, _name, "i") //Beosin de la commande Mode pour mettre le +i sur IRC
};
	std::vector<std::string> _rpls(_rpl, _rpl + sizeof(_rpl) / sizeof(_rpl[0]));
	switch (find_cmds())
	{
	case 0:
	{
            setup_nick();
			if (_regis)
			{
				std::cout << "The registration is finished\n"; 
				_server->sendfds_serv(_so, _rpls);	
			}
			break;
	}
    case 1:
	{
            setup_user();
			if (_regis)
			{
				std::cout << "The registration is finished\n"; 
				_server->sendfds_serv(_so, _rpls);
			}
            break ;	
	}
	default:
		break;
	}
}


void User::cmds()
{
	std::vector<std::string> _rpl;
	switch (find_cmds())
	{
	case 1:
	{
		setup_nick();
		break ;
	}
	case 2:
	{
		break ;
	}
	case 3:
	{	
		_rpl.push_back(RPL_PING(_server, _name, _str.substr(0, 5)));
		_server->sendfds_serv(_so, _rpl);
		break ;
	}
	case 4:
	{
		_rpl.push_back(RPL_PONG(_server, _name, _str.substr(0, 5)));
		_server->sendfds_serv(_so, _rpl);
		break ;
	}
	default:
		break;
	}
}

void User::trim_cmds(size_t _endcmds)
{
	size_t _len = 0;
	bool double_point = 0;
	for (size_t i = 0; i < _endcmds; i++)
	{
		_len = 0;
		if (_str[i] == ':')
			double_point = 1;
		while(isspace(_str[i++]))
			_len++;
		if (_len > 1 && !double_point)
			_str = _str.erase(i - _len, _len - 1);
	}
}

void User::setup_nick()
{
    size_t _index = _str.find(' ');
    size_t _len = 0;
	std::string _valid = "\\[]{}";
	if (_index == _str.size() -3 || _index == std::string::npos || isdigit(_str[_index + 1]))
	{
		std::cout << "you forgot the parameter" << std::endl;
		return ;
	}
    while (++_index < _str.find("\r\n"))
    {
        if(!isalnum(_str[_index]) && std::find(_valid.begin(), _valid.end(), _str[_index]) != _valid.end())
        {
            std::cout << "Error nickname\n";
            return ;
        }
        _len++;
    }
	std::cout << "Setup NICK\n";
	std::cout << "len of nickname : " << _len << std::endl;
    _name.append(_str, _str.find(' ') + 1, _len);
    if (!_name.empty() && !_username.empty())
        _regis = 1;

       
}

void User::setup_user()
{
    size_t _usern = 0;
    size_t _rn = 0;
	size_t _index = _str.find(' ');
	if (_index == _str.size() -2 || _index == std::string::npos)
	{
		std::cout << "you forgot the parameter" << std::endl;
		return ;
	}
	std::cout << "first space : " <<_index << std::endl;
	while(isalpha(_str[++_index]))
        _usern++;
 	_index = _str.find(' ', _index);
	std::cout << "second space : " <<_index << std::endl;
	_index = _str.find(' ', ++_index);
	std::cout << "third space : " <<_index << std::endl;
	_index = _str.find(' ', ++_index);
	std::cout << "fourth space : " <<_index << std::endl;
	if (_str[++_index] != ':')
		--_index;
	while((isalpha(_str[++_index]) || isspace(_str[_index])) && _index < _str.size() -2)
        _rn++;
	if(_usern > 0 && _rn > 0)
	{
		std::cout << "Setup username \t realname\n";
 		_username.append(_str, _str.find(' ') + 1, _usern);
 		_realname.append(_str, _index - _rn, _rn);
		std::cout << "Username : " << _username << std::endl;
		std::cout << "Realname : " << _realname << std::endl;
	}
	if(!_name.empty() && !_username.empty())
		_regis = 1;
}