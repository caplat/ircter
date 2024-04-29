#include "User.hpp"

User::User(int fd, Server &_serv) : _userMode("irO"), _so(fd), _regis(0), _server(&_serv){
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
			trim_cmds(_end);
			if (!_regis)
				cmds_register();
			else
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
	const char* tab[] = {"NICK", "USER", "PING", "PONG", "JOIN", "MODE"};
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
	switch (find_cmds())
	{
	case 0:
            setup_nick();
			break;
    case 1:
	{
            setup_user();
			_server->sendfds_serv(_so);
            break ;	
	}
	default:
		break;
	}
	if (_regis)
	{
		_server->set_rpl(RPL_WELCOME(_server, _name));
		_server->set_rpl(RPL_YOURHOST(_server, _name));
		_server->set_rpl(RPL_CREATED(_server, _name));
		_server->set_rpl(RPL_MYINFO(_server, _name));
		_server->set_rpl(RPL_ISUPPORT(_server, _name));
		_server->set_rpl(RPL_MOTD(_server, _name));
		_server->set_rpl(RPL_ENDOFMOTD(_server, _name));
		_server->set_rpl(RPL_UMODEIS(_server, _name, "i")); //Beosin de la commande Mode pour mettre le +i sur IRC
		_server->sendfds_serv(_so);
		_server->clear_rpl();
	}
}


void User::cmds()
{
	try
	{
		switch (find_cmds())
		{
		case 0:
		{
			setup_nick();
			break ;
		}
		case 1:
		{
			break ;
		}
		case 2:
		{	
			_server->set_rpl(RPL_PING(_server, _name, _str.substr(0, 5)));
			break ;
		}
		case 3:
		{
			_server->set_rpl(RPL_PONG(_server, _name, _str.substr(0, 5)));
			break ;
		}
		case 4:
		{
			std::cout << "Join\n";
			break ;
		}
		case 5:
		{
			std::cout << "MODE" << std::endl;
			set_mode();
			_server->set_rpl(RPL_MODE(_server, _name, _userMode));
			break ;
		}
		default:
			break;
		}
		_server->sendfds_serv(_so);
		_server->clear_rpl();
	}
	catch(std::string &what)
	{
		_server->set_rpl(what);
		_server->sendfds_serv(_so);
		_server->clear_rpl();
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
	while(isalpha(_str[++_index]))
        _usern++;
 	_index = _str.find(' ', _index);
	_index = _str.find(' ', ++_index);
	_index = _str.find(' ', ++_index);
	if (_str[++_index] != ':')
		--_index;
	while((isalpha(_str[++_index]) || isspace(_str[_index])) && _index < _str.size() -2)
        _rn++;
	if(_usern > 0 && _rn > 0)
	{
 		_username.append(_str, _str.find(' ') + 1, _usern);
 		_realname.append(_str, _index - _rn, _rn);
	}
	if(!_name.empty() && !_username.empty())
		_regis = 1;
}

void User::set_mode()
{
	size_t _index;
	int	_signe = 1;
	_index = _str.compare(_str.find(' ') + 1, _name.size(), _name) ;
	if (_index)
		throw ERR_USERSDONTMATCH(_server, _name);
	_index = _str.find(_name, _str.find(' ')) + _name.size();
	while (_index < _str.size() -2 && (_str.find_first_of("+-", _index) != std::string::npos || isspace(_str[_index])))
	{
		if (_str[_index] == '+')
			_signe = 1;
		else if (_str[_index] == '-')
			_signe *= -1;
		else if (!isspace(_str[_index]))
			_signe = 0;
		if (_signe == 0)
			return ;
		while(isalpha(_str[++_index]) && _index < _str.size() - 2)
		{
			if (_str.find_first_of("irO", _index) != std::string::npos)
			{
				if (_signe == 1 && _userMode.find(_str[_index]) == std::string::npos)
					_userMode.push_back(_str[_index]);
				else if (_signe == -1 && _userMode.find(_str[_index]) != std::string::npos)
					_userMode.erase(_userMode.find(_str[_index]));
			}
		}
	}
}