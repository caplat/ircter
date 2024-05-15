#include "User.hpp"

User::User(int fd, Server &_serv) : _userMode(""), _so(fd), _regis(0), _server(&_serv){
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


std::string User::get_name()
{
	return (_name);
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
       		    throw(std::string("no \\r\\n"));
			_cmd = _str.substr(0, _end);
			trim_cmds();
			if (!_regis)
				cmds_register();
			else
				cmds();
        }
        catch (std::string &test)
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
		if (_cmd.compare(0, 4, *_it) == 0)
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
		_server->sendfds_serv(_so);
	}
	_cmd.clear();
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
			_server->set_rpl(RPL_PING(_server, _name, _cmd.substr(0, 5)));
			break ;
		}
		case 3:
		{
			_server->set_rpl(RPL_PONG(_server, _name, _cmd.substr(0, 5)));
			break ;
		}
		case 4:
		{
			std::cout << "Join\n";
			join();
			break ;
		}
		case 5:
		{
			set_mode();
			break ;
		}
		default:
			break;
		}
		_server->sendfds_serv(_so);
		_cmd.clear();
	}
	catch(std::string &what)
	{
		_server->set_rpl(what);
		_server->sendfds_serv(_so);
		_cmd.clear();
	}
}

void User::trim_cmds()
{
	size_t _len = 0;
	bool double_point = 0;
	for (size_t i = 0; i < _cmd.size(); i++)
	{
		_len = 0;
		if (_cmd[i] == ':')
			double_point = 1;
		while(isspace(_cmd[i++]))
			_len++;
		if (_len > 1 && !double_point)
			_cmd = _cmd.erase(i - _len, _len - 1);
	}
}

void User::setup_nick()
{
    size_t _index = _cmd.find(' ');
	std::string _valid = "\\[]{}";
	if (_index == _cmd.size() - 1|| _index == std::string::npos || isdigit(_cmd[_index + 1]))
		throw (ERR_NONICKNAMEGIVEN(_server, _name));
    while (++_index < _cmd.size())
    {
        if(!isalnum(_cmd[_index]) && std::find(_valid.begin(), _valid.end(), _cmd[_index]) != _valid.end())
			throw (ERR_ERRONEUSNICKNAME(_server, _name));
    }
	if (_server->findUserbyname(_cmd.substr(_cmd.find(' ') + 1)))
		throw (ERR_NICKNAMEINUSE(_server, _name, _cmd.substr(_cmd.find(' ') + 1)));
	std::string _oldname = _name;
	_name.clear();
	_name.append(_cmd, _cmd.find(' ') + 1);
    if (!_name.empty() && !_username.empty() && _regis == 0)
        _regis = 1;
	else if (_regis == 1)
	{
		_server->set_rpl(RPL_NICK(_server, _oldname, _name));
	}     
}

void User::setup_user()
{
    size_t _usern = 0;
    size_t _rn = 0;
	size_t _index = _cmd.find(' ');
	if (_index == _cmd.size() - 1 || _index == std::string::npos)
	{
		std::cout << "you forgot the parameter" << std::endl;
		return ;
	}
	while(isalpha(_cmd[++_index]))
        _usern++;
 	_index = _cmd.find(' ', _index);
	_index = _cmd.find(' ', ++_index);
	_index = _cmd.find(' ', ++_index);
	if (_cmd[++_index] != ':')
		--_index;
	while((isalpha(_cmd[++_index]) || isspace(_cmd[_index])) && _index < _cmd.size())
        _rn++;
	if(_usern > 0 && _rn > 0)
	{
 		_username.append(_cmd, _cmd.find(' ') + 1, _usern);
 		_realname.append(_cmd, _index - _rn, _rn);
	}
	if(!_name.empty() && !_username.empty())
		_regis = 1;
}

void User::set_mode()
{
	size_t _index;
	int	_signe = 1;
	_index = _cmd.compare(_cmd.find(' ') + 1, _name.size(), _name) ;
	if (_index)
		throw ERR_USERSDONTMATCH(_server, _name);
	_index = _cmd.find(_name, _str.find(' ')) + _name.size();
	if (_index == _cmd.size())
		throw RPL_UMODEIS(_server, _name, _userMode);
	while (_index < _cmd.size() && (_cmd.find_first_of("+-", _index) != std::string::npos || isspace(_cmd[_index])))
	{
		if (_cmd[_index] == '+')
			_signe = 1;
		else if (_cmd[_index] == '-' && _signe != -1)
			_signe *= -1;
		else if (!isspace(_cmd[_index]) && !(std::string("+-").find(_cmd[_index])) && !isalpha(_cmd[_index]))
			_signe = 0;
		if (_signe == 0)
			throw (std::string("PB syntaxe"));
		while(isalpha(_cmd[++_index]) && _index < _cmd.size())
		{
			std::cout << _cmd[_index] << std::endl;
			if (std::string("irO").find(_cmd[_index]) != std::string::npos)
			{
				if (_signe == 1 && _userMode.find(_cmd[_index]) == std::string::npos)
				{
					_userMode.push_back(_cmd[_index]);
					_server->set_rpl(RPL_MODE(_server, _name, "+", _cmd.substr(_index, 1)));
				}
				else if (_signe == -1 && _userMode.find(_cmd[_index]) != std::string::npos)
				{
					if (_userMode.size() == 1)
						_userMode.clear();
					else
					{
						_userMode.erase(_userMode.find(_cmd[_index]),_userMode.find(_cmd[_index]));
					}
					_server->set_rpl(RPL_MODE(_server, _name, "-", _cmd.substr(_index, 1)));
				}
			}
			else
			{
				_server->set_rpl(ERR_UMODEUNKNOWNFLAG(_server, _name));
			}
		}
	}
}

void User::join()
{
	std::string _sub = _cmd.substr(_cmd.find_last_of(' '));
	Chan* _exist = _server->already_channel(to_upper(_sub));
	std::cout << "sub: " << _sub << std::endl;
	if (!_exist)
	{
		Chan *_new_chan = new Chan(*this, _sub);
		_chan.push_back(_new_chan);
		_server->set_channel(_new_chan);
		std::cout << "User class " << _chan[0]->get_name() << std::endl;
		_server->set_rpl(RPL_JOIN(_server, _name, _cmd, _sub));
		_server->set_rpl(RPL_NAMREPLY(_server, _name, _new_chan->get_name(), _new_chan->string_for_rpl()));
		_server->set_rpl(RPL_ENDOFNAMES(_server, _name, _new_chan->get_name()));
	}
	else
	{

	_server->set_rpl(RPL_NAMREPLY(_server, _name, _exist->get_name(), _exist->string_for_rpl()));
	}
}


